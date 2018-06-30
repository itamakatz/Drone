#ifndef __SIX_DFO__
#define __SIX_DFO__

#include "IMU_Controller.h"
#include "IMU_ADXL345.h"
#include "IMU_ITG3200.h"

#include <i2c_t3.h>
#include "debug_def.h"
#include "general_defs.h"
#include "Cyc_array_6DoF.h"

class s6DoF {
private:
	IMU_Controller _IMU_controller;
	Cyc_array_6DoF _c_array[3];

	float _average[3];
	float _average_zero_offset[3];

	float _angles_Euler[3];
	float _angles_Euler_zero_offset[3];
	
	float _weights;
	float _alpha;

	void _init_samples();
	void _update_average(); 

public:
	s6DoF(){}
	void sixDOF_setup(float alpha);
	void sixDOF_loop();
	void get_angles(float* angles_average);
	void get_average(float* angles_Euler);
	void calibrate();
	void set_zero();
};

#endif