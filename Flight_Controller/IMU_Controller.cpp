/*
IMU_Controller.cpp - A libre and easy to use orientation sensing library for Arduino
Copyright (C) 2011 Fabio Varesano <fabio at varesano dot net>

Development of this code has been supported by the Department of Computer Science,
Universita' degli Studi di Torino, Italy within the Piemonte Project
http://www.piemonte.di.unito.it/


This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.	If not, see <http://www.gnu.org/licenses/>.

*/

#include <inttypes.h>
#include "IMU_Controller.h"
// #include "WireUtils.h"
// #include "general_defs.h"

// for the new invSqrt. maybe not needed since it compiles without it (for teensy 3.6) 
#include <stdint.h>
#include <string.h>

IMU_Controller::IMU_Controller() {
	acc = ADXL345();
	gyro = ITG3200();
	
	// initialize quaternion
	q0 = 1.0f;
	q1 = 0.0f;
	q2 = 0.0f;
	q3 = 0.0f;
	exInt = 0.0;
	eyInt = 0.0;
	ezInt = 0.0;
	twoKp = twoKpDef;
	twoKi = twoKiDef;
	integralFBx = 0.0f,	integralFBy = 0.0f, integralFBz = 0.0f;
	lastUpdate = 0;
	now = 0;
}

void IMU_Controller::init() {
	init(IMU_ACC_ADDR, IMU_ITG3200_DEF_ADDR);
}

void IMU_Controller::init(int acc_addr, int gyro_addr) {
	delay(5);
	
	// init ADXL345
	acc.init(acc_addr);
	gyro.init(gyro_addr);
	delay(1000);
	// calibrate the ITG3200
	gyro.zeroCalibrate(128,5);
}


void IMU_Controller::getRawValues(int16_t * raw_values) {
	acc.readAccel(&raw_values[0], &raw_values[1], &raw_values[2]);
	gyro.readGyroRaw(&raw_values[3], &raw_values[4], &raw_values[5]);
}


void IMU_Controller::getValues(float * values) {	
	int16_t accval[3];
	acc.readAccel(&accval[0], &accval[1], &accval[2]);
	values[0] = ((float) accval[0]);
	values[1] = ((float) accval[1]);
	values[2] = ((float) accval[2]);
	
	gyro.readGyro(&values[3]);
}


// Quaternion implementation of the 'DCM filter' [Mayhony et al].	Incorporates the magnetic distortion
// compensation algorithms from Sebastian Madgwick filter which eliminates the need for a reference
// direction of flux (bx bz) to be predefined and limits the effect of magnetic distortions to yaw
// axis only.
//
// See: http://x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
//=====================================================================================================
void IMU_Controller::AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az) {
	float recipNorm;
	float q0q0, q0q1, q0q2, q1q3, q2q3, q3q3;
	float halfex = 0.0f, halfey = 0.0f, halfez = 0.0f;
	float qa, qb, qc;

	// Auxiliary variables to avoid repeated arithmetic
	q0q0 = q0 * q0;
	q0q1 = q0 * q1;
	q0q2 = q0 * q2;
	q1q3 = q1 * q3;
	q2q3 = q2 * q3;
	q3q3 = q3 * q3;

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if((ax != 0.0f) && (ay != 0.0f) && (az != 0.0f)) {
		float halfvx, halfvy, halfvz;
		
		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;
		
		// Estimated direction of gravity
		halfvx = q1q3 - q0q2;
		halfvy = q0q1 + q2q3;
		halfvz = q0q0 - 0.5f + q3q3;
	
		// Error is sum of cross product between estimated direction and measured direction of field vectors
		halfex += (ay * halfvz - az * halfvy);
		halfey += (az * halfvx - ax * halfvz);
		halfez += (ax * halfvy - ay * halfvx);
	}

	// Apply feedback only when valid data has been gathered from the accelerometer or magnetometer
	if(halfex != 0.0f && halfey != 0.0f && halfez != 0.0f) {
		// Compute and apply integral feedback if enabled
		if(twoKi > 0.0f) {
			integralFBx += twoKi * halfex * (1.0f / sampleFreq);	// integral error scaled by Ki
			integralFBy += twoKi * halfey * (1.0f / sampleFreq);
			integralFBz += twoKi * halfez * (1.0f / sampleFreq);
			gx += integralFBx;	// apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		}
		else {
			integralFBx = 0.0f; // prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}
	
	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / sampleFreq));	 // pre-multiply common factors
	gy *= (0.5f * (1.0f / sampleFreq));
	gz *= (0.5f * (1.0f / sampleFreq));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);
	
	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}


void IMU_Controller::getQ(float * q) {
	float val[6];
	getValues(val);
	
	// DEBUG_PRINT_LN(val[3] * M_PI/180);
	// DEBUG_PRINT_LN(val[4] * M_PI/180);
	// DEBUG_PRINT_LN(val[5] * M_PI/180);
	// DEBUG_PRINT_LN(val[0]);
	// DEBUG_PRINT_LN(val[1]);
	// DEBUG_PRINT_LN(val[2]);
	// DEBUG_PRINT_LN(val[6]);
	// DEBUG_PRINT_LN(val[7]);
	// DEBUG_PRINT_LN(val[8]);
	
	now = micros();
	sampleFreq = 1.0 / ((now - lastUpdate) / 1000000.0);
	lastUpdate = now;
	// gyro values are expressed in deg/sec, the * M_PI/180 will convert it to radians/sec
	// use the call below when using a 6DOF IMU
	AHRSupdate(val[3] * M_PI/180, val[4] * M_PI/180, val[5] * M_PI/180, val[0], val[1], val[2]);
	q[0] = q0;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
}

// Returns the Euler angles in radians defined with the Aerospace sequence.
// See Sebastian O.H. Madwick report 
// "An efficient orientation filter for inertial and intertial/magnetic sensor arrays" Chapter 2 Quaternion representation
void IMU_Controller::getEuler(float * angles) {
float q[4]; // quaternion
	getQ(q);
	angles[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1) * 180/M_PI; // psi
	angles[1] = -asin(2 * q[1] * q[3] + 2 * q[0] * q[2]) * 180/M_PI; // theta
	angles[2] = atan2(2 * q[2] * q[3] - 2 * q[0] * q[1], 2 * q[0] * q[0] + 2 * q[3] * q[3] - 1) * 180/M_PI; // phi
}


void IMU_Controller::getAngles(float * angles) {
	float a[3]; //Euler
	getEuler(a);

	angles[0] = a[0];
	angles[1] = a[1];
	angles[2] = a[2];
	
	if(angles[0] < 0)angles[0] += 360;
	if(angles[1] < 0)angles[1] += 360;
	if(angles[2] < 0)angles[2] += 360;

}


void IMU_Controller::getYawPitchRoll(float * ypr) {
	float q[4]; // quaternion
	float gx, gy, gz; // estimated gravity direction
	getQ(q);
	
	gx = 2 * (q[1]*q[3] - q[0]*q[2]);
	gy = 2 * (q[0]*q[1] + q[2]*q[3]);
	gz = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];
	
	ypr[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1) * 180/M_PI;
	ypr[1] = atan(gx / sqrt(gy*gy + gz*gz))	* 180/M_PI;
	ypr[2] = atan(gy / sqrt(gx*gx + gz*gz))	* 180/M_PI;
}


float invSqrt(float number) {
	volatile float x = number * 0.5F;
	volatile float y = number;
	volatile long i;

    char* y_p = (char*)&y;
    char* i_p = (char*)&i;
    memcpy(i_p, y_p, sizeof(y));

	i = 0x5f375a86 - ( i >> 1 );

    memcpy(y_p, i_p, sizeof(i));

	volatile const float f = 1.5F;
	y = y * ( f - ( x * y * y ) );
	return y;
}