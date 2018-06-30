#include "Motor.h"

// unsigned long MIN_THROTTLE_OUTPUT = map(BLHEliSuit_MIN_THROTTLE - OFF_THROTTLE_OFFSET,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);
// unsigned long MAX_THROTTLE_OUTPUT = map(BLHEliSuit_MAX_THROTTLE,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);

Motor::Motor(uint8_t pin, Motor_spin_dir dir) {
	_pin = pin;
	_spin_dir = dir;
	// _min_input_signal = MIN_MAX_INPUT_SIGNAL;
	// _max_input_signal = MIN_MAX_INPUT_SIGNAL;
}

uint8_t Motor::get_motor_pin(){
	return _pin;
}

void Motor::set_motor_speed(unsigned long motor_speed){
	// if (_min_input_signal > channel_input) {
	// 	_min_input_signal = channel_input;
	// }
	// if (_max_input_signal < channel_input) {
	// 	_max_input_signal = channel_input;
	// }

	_motor_speed = motor_speed;

	// _last_channel_input = channel_input;
}

void Motor::set_motor_speed_change(long change){
	// ???? _motor_speed += scale(change, 0.0, 1.0, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

Motor_spin_dir Motor::get_motor_spin(){
	return _spin_dir;
}

unsigned long Motor::get_motor_speed(){
	return _motor_speed;
}

// unsigned long Motor::get_min_input_signal(){
// 	return _min_input_signal;
// }

// unsigned long Motor::get_max_input_signal(){
// 	return _max_input_signal;
// }

// void Motor::reset_motor_boundries(){
// 	_min_input_signal = MIN_MAX_INPUT_SIGNAL;
// 	_max_input_signal = MIN_MAX_INPUT_SIGNAL;
// }

