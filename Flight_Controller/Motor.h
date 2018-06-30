#ifndef __MOTOR__
#define __MOTOR__

#include "debug_def.h"
#include "general_defs.h"

enum Motor_spin_dir { CW_Spin, CCW_Spin };

class Motor {
private:
	uint8_t _pin;
	// unsigned long _min_input_signal = 0;
	// unsigned long _max_input_signal = 0;
	unsigned long _last_channel_input = 0;
	unsigned long _motor_speed = 0;
	Motor_spin_dir _spin_dir;
	
public:
	Motor(){}
	Motor(uint8_t pin, Motor_spin_dir dir);
	void set_motor_speed(unsigned long motor_speed);
	void set_motor_speed_change(long change);
	uint8_t get_motor_pin();
	Motor_spin_dir get_motor_spin();
	unsigned long get_motor_speed();
	// unsigned long get_min_input_signal();
	// unsigned long get_max_input_signal();
	// void reset_motor_boundries();
};

#endif