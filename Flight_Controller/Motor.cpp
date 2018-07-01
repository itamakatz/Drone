#include "Motor.h"

Motor::Motor(uint8_t pin, Motor_spin_dir dir) {
	_pin = pin;
	_spin_dir = dir;
}

void Motor::set_motor_speed(unsigned long motor_speed){
	_motor_speed = motor_speed;
}

uint8_t Motor::get_motor_pin(){
	return _pin;
}

Motor_spin_dir Motor::get_motor_spin(){
	return _spin_dir;
}

unsigned long Motor::get_motor_speed(){
	return _motor_speed;
}