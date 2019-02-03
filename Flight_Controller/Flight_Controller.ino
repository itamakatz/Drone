#include "s6DoF.h"
#include <Metro.h>
#include <i2c_t3.h>
#include "debug_def.h"
#include "general_defs.h"
#include "SimpleFIFO.h"
#include "Motor.h"
#include "Channel.h"

#ifndef DEBUG_FUNC_FLOW_main_ino
	#ifdef DEBUG_FUNC_FLOW
		#undef DEBUG_FUNC_FLOW
		#define DEBUG_FUNC_FLOW(str)
	#endif
#endif

#ifndef DEBUG_PRINT_main_ino
	#ifdef DEBUG_PRINT
		#undef DEBUG_PRINT
		#define DEBUG_PRINT(str)
	#endif
	#ifdef DEBUG_PRINT_VAL
		#undef DEBUG_PRINT_VAL
		#define DEBUG_PRINT_VAL(val)
	#endif
#endif

// ================================================================= Incredibly stable IMU scheme!!!!! ================================================================= //
/*
Servo myservo;  // create servo object to control a servo
// PWMServo myservo;  // create servo object to control a servo
IntervalTimer sensors_correction_timer;
IntervalTimer print_status_timer;
float correction = 0;
float sample = 0;
float move_to = 0;

float angles_Euler[3] = {0};
float angles_Euler_average[3] = {0};
s6DoF s6DoF_object = s6DoF();

Piezo_modes last_mode = none;
SimpleFIFO<int, 10> piezo_fifo;

void setup(){


  	// myservo.attach(SERVO_PIN_A, 1000, 2000); // some motors need min/max setting
  	// myservo.attach(SERVO_PIN_A, 400, 2600); // some motors need min/max setting
  	myservo.attach(9, 400, 2600); // some motors need min/max setting

	#ifdef DEBUG_FUNC_FLOW_main_ino
		delay(INITIAL_DELAY_main_ino);
	#endif

	Serial.begin(115200);
	Wire.begin();

	// set AnalogWrite resolution
	analogWriteResolution(ANALOGWRITE_BIT_RESOLUTION);

	// set output PWM frequency of the piezo
	analogWriteFrequency(PIEZO_PIN, ANALOGWRITE_FREQUENCY);

	DEBUG_FUNC_FLOW("setup: after Wire.begin()");

	s6DoF_object.sixDOF_setup(sixDOF_ALPHA);
	pinMode(LED_PIN, OUTPUT);
	digitalWriteFast(LED_PIN, HIGH);
	
	s6DoF_object.sixDOF_loop();
	s6DoF_object.get_angles(&angles_Euler[0]);
	s6DoF_object.get_average(&angles_Euler_average[0]);

	sensors_correction_timer.begin(sensors_correction, 100000);
	sensors_correction_timer.priority(250);

	print_status_timer.begin(print_status, 1000000);
	print_status_timer.priority(255);
	DEBUG_FUNC_FLOW("setup: after objects init");
}

void loop(){

	DEBUG_FUNC_FLOW("loop: beginning");
	// Serial.println("loop: beginning");

	check_metros();

	s6DoF_object.sixDOF_loop();
	s6DoF_object.get_angles(&angles_Euler[0]);
	s6DoF_object.get_average(&angles_Euler_average[0]);
	
	// Serial.print("angles_Euler: ");
	// Serial.print(angles_Euler[0]);
	// Serial.print(", ");
	// Serial.print(angles_Euler[1]);
	// Serial.print(", ");
	// Serial.println(angles_Euler[2]);

	// Serial.print("angles_Euler_average: ");
	// Serial.print(angles_Euler_average[0]);
	// Serial.print(", ");
	// Serial.print(angles_Euler_average[1]);
	// Serial.print(", ");
	// Serial.println(angles_Euler_average[2]);


	// scale it to use it with the servo (value between 0 and 180)
	float min_IMU = -70;
	float max_IMU = 70;
	float min_Servo = 400;
	float max_Servo = 2600;

	sample = angles_Euler[0] + correction;
	if(sample < min_IMU ){ sample = min_IMU; }
	if(sample > max_IMU ){ sample = max_IMU; }

	move_to = float_map(sample, min_IMU, max_IMU, min_Servo, max_Servo);     
	// float move_to = float_map(sample, min_IMU, max_IMU, 0, 179);     
	// float val = float_map(angles_Euler[0], -150, 150, 0, 179);     
	// float val = float_map(angles_Euler[0], -179, 179, 0, 300);     
	// float val = float_map(angles_Euler[0], -179, 179, 0, 179);     
	
	// sets the servo position according to the scaled value
	// myservo.write(move_to);     
	myservo.writeMicroseconds(move_to);     
	             
	// Serial.println("loop: end");

	DEBUG_FUNC_FLOW("loop: after updating objects");

	// delay(CRITICAL_DELAY_LOOP_main_ino);
}

void sensors_correction(){
	correction = (angles_Euler[0] + correction) * 0.01;
}

void print_status(){
	Serial.print("angles_Euler[0]: ");
	Serial.println(angles_Euler[0]);
	Serial.print("correction: ");
	Serial.println(correction);
	Serial.print("sample: ");
	Serial.println(sample);
	Serial.print("move_to: ");
	Serial.println(move_to);
	Serial.println();
}

void Move_Servo(int move_to_serial){
	Serial.print("move_to_serial: ");
	Serial.println(move_to_serial);

	myservo.write(move_to_serial);                  
}

float float_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/
uint8_t motor_pins[NUM_OF_MOTORS] = {23, 22, 21, 20};
// uint8_t channel_pins[NUM_OF_CHANNELS] = {2, 3, 4, 5, 6, 7, 8, 9};
// channel number -                        {1, 2, 3, 4, 5, 6, 7, 8};

uint8_t channel_thrust_pins[NUM_OF_TRHROTTLE_CHANNELS] = {2, 3, 4, 5, 7, 9};
uint8_t channel_switch_pins[NUM_OF_SWITCH_CHANNELS] = {6, 8};

float angles_Euler[3] = {0};
// float angles_Euler_average[3] = {0};
s6DoF s6DoF_object = s6DoF();

// float iTerm[3] = {0, 0, 0};
// float lastError[3] = {0, 0, 0};
// float target_angles[3] = {0, 0, 0};
// float PIDValue[3] = {0,0,0};

Piezo_modes last_mode = none;
SimpleFIFO<int,10> piezo_fifo;

Motor all_motors[NUM_OF_MOTORS];
Channel_Throttle throttle_channels[NUM_OF_TRHROTTLE_CHANNELS];
Channel_Switch switch_channels[NUM_OF_SWITCH_CHANNELS];

bool run = false;
bool rc_on = false;
// bool target_angles_is_set = false;

void setup(){

	// set AnalogWrite resolution
	analogWriteResolution(ANALOGWRITE_BIT_RESOLUTION);

	// CRUCIAL - FIRST THING TO DO: SHUT OFF MOTORS 
	for (int i = 0; i < NUM_OF_MOTORS; ++i) { analogWrite(motor_pins[i], 0); }

	#ifdef DEBUG_FUNC_FLOW_main_ino
		delay(INITIAL_DELAY_main_ino);
	#endif

	Serial.begin(115200);
	Wire.begin();

	// set output PWM frequency of the piezo
	analogWriteFrequency(PIEZO_PIN, ANALOGWRITE_FREQUENCY);

	DEBUG_FUNC_FLOW("setup: after Wire.begin()");

	// s6DoF_object.sixDOF_setup(sixDOF_ALPHA);
	s6DoF_object.sixDOF_setup();
	pinMode(LED_PIN, OUTPUT);
	digitalWriteFast(LED_PIN, HIGH);
	
	RC_setup();

	DEBUG_FUNC_FLOW("setup: after objects init");
}

void loop(){

	DEBUG_FUNC_FLOW("loop: beginning");

	check_metros();

	s6DoF_object.sixDOF_loop();
	s6DoF_object.get_angles(&angles_Euler[0]);
	// s6DoF_object.get_average(&angles_Euler_average[0]);
	
	RC_loop();

	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		all_motors[i].set_motor_speed(0);
	}

	if (run) {

		// movement derived from RC; altitude MUST be the first one because of absolute messurments
		altitude(throttle_channels[ALTITUDE_CH].calc_channel_change());

		yaw(throttle_channels[YAW_CH].calc_channel_change());
		roll(throttle_channels[ROLL_CH].calc_channel_change());
		pitch(throttle_channels[PITCH_CH].calc_channel_change());
		
		// PID();

		// all_motors[i].set_motor_speed_change(PIDValue[i]);

		// all_motors[B_R_INDEX].set_motor_speed(MAX_THROTTLE_OUTPUT);

	}

	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		analogWrite(all_motors[i].get_motor_pin(), all_motors[i].get_motor_speed());
	}

	DEBUG_FUNC_FLOW("loop: after updating objects");

	delay(CRITICAL_DELAY_LOOP_main_ino);
}

// void PID(){
// 	for (int i = 0; i < 3; ++i) {
// 		float error = (target_angles[i] - angles_Euler_average[i]);
// 		float pTerm = Kp * error;
// 		iTerm[i] += Ki * error;
// 		float dTerm = Kd * (error - lastError[i]);
// 		lastError[i] = error;
// 		PIDValue[i] = pTerm + iTerm[i] + dTerm;
// 	}
// }

// unsigned long scale(double input, double inputMin, double inputMax, unsigned long  outputMin, unsigned long outputMax) { // Like map() just returns a double
// 	unsigned long output;
// 	if(inputMin < inputMax)
// 		output = unsigned long((input - inputMin) / (inputMax - inputMin) * (outputMax - outputMin));							
// 	else
// 		output = unsigned long((inputMin - input) / (inputMin - inputMax) * (outputMax - outputMin));	

// 	if(output > outputMax)
// 		output = outputMax;
// 	else if(output < outputMin)
// 		output = outputMin;

// 	return output;
// }