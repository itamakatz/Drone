#include "Motor.h"

Motor::Motor(uint8_t pin, Motor_spin_dir dir) {
	_pin = pin;
	_spin_dir = dir;
	_speed = 0;
}

void Motor::set_absolute_speed(long new_speed){
	
	if (new_speed == 0){
		_speed = MIN_OFFSET_THROTTLE_OUTPUT;
	} else if ((unsigned long) new_speed <= MIN_THROTTLE_OUTPUT) {
		_speed = MIN_THROTTLE_OUTPUT;
	} else if ((unsigned long) new_speed >= MAX_THROTTLE_OUTPUT){
		_speed = MAX_THROTTLE_OUTPUT;
	} else {
		_speed = new_speed;
	}	
}

void Motor::set_relative_speed(long speed_change){
	set_absolute_speed(_speed + speed_change);
}

uint8_t Motor::get_pin(){
	return _pin;
}

Motor_spin_dir Motor::get_spin(){
	return _spin_dir;
}

long Motor::get_speed(){
	return _speed;
}