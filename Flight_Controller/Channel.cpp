#include "Channel.h"

unsigned long MIN_THROTTLE_OUTPUT = map(BLHEliSuit_MIN_THROTTLE - OFF_THROTTLE_OFFSET,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);
unsigned long MAX_THROTTLE_OUTPUT = map(BLHEliSuit_MAX_THROTTLE,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);

Channel::Channel(uint8_t pin){
	_pin = pin;
	_min_input_signal = MIN_MAX_INPUT_SIGNAL;
	_max_input_signal = MIN_MAX_INPUT_SIGNAL;
}

void Channel::read_new_raw_signal(unsigned long channel_input){
	if (_min_input_signal > channel_input) {
		_min_input_signal = channel_input;
	}
	if (_max_input_signal < channel_input) {
		_max_input_signal = channel_input;
	}

	_last_channel_input = _new_channel_input;
	_new_channel_input = map(channel_input, _min_input_signal, _max_input_signal, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

uint8_t Channel::get_channel_pin(){
	return _pin;
}

long Channel::get_channel_difference(){
	return (_last_channel_input - _new_channel_input);
}

unsigned long Channel::get_new_channel_input(){
	return _new_channel_input;
}

unsigned long Channel::get_min_input_signal(){
	return _min_input_signal;
}

unsigned long Channel::get_max_input_signal(){
	return _max_input_signal;
}

void Channel::reset_channel_boundries(){
	_min_input_signal = MIN_MAX_INPUT_SIGNAL;
	_max_input_signal = MIN_MAX_INPUT_SIGNAL;
}