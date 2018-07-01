#include "Motor.h"

Motor::Motor(uint8_t pin, Motor_spin_dir dir) {
	_pin = pin;
	_spin_dir = dir;
	_motor_speed = 0;
}

void Motor::set_motor_speed(long motor_speed){
	
	// if (motor_speed == 0){
	// 	_motor_speed = 0;
	// } else if (motor_speed <= MIN_THROTTLE_OUTPUT) {
	if (motor_speed <= MIN_THROTTLE_OUTPUT) {
		_motor_speed = MIN_THROTTLE_OUTPUT;
	} else if (motor_speed >= MAX_THROTTLE_OUTPUT){
		_motor_speed = MAX_THROTTLE_OUTPUT;
	} else {
		_motor_speed = motor_speed;
	}	
}

uint8_t Motor::get_motor_pin(){
	return _pin;
}

Motor_spin_dir Motor::get_motor_spin(){
	return _spin_dir;
}

long Motor::get_motor_speed(){
	return _motor_speed;
}