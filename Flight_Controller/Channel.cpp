#include "Channel.h"

unsigned long MIN_THROTTLE_OUTPUT = map(BLHEliSuit_MIN_THROTTLE - OFF_THROTTLE_OFFSET,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);
unsigned long MAX_THROTTLE_OUTPUT = map(BLHEliSuit_MAX_THROTTLE,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);

void Channel_Throttle::reset_channel_boundries(){
	_min_input_signal = MIN_MAX_INPUT_SIGNAL;
	_max_input_signal = MIN_MAX_INPUT_SIGNAL;
}

long Channel_Throttle::get_channel_difference(){
	return (_last_channel_input - _new_channel_input);
}


void Channel_Throttle::read_new_raw_signal(unsigned long channel_input){
	if (_min_input_signal > channel_input) {
		_min_input_signal = channel_input;
	}
	if (_max_input_signal < channel_input) {
		_max_input_signal = channel_input;
	}

	_last_channel_input = _new_channel_input;
	_new_channel_input = map(channel_input, _min_input_signal, _max_input_signal, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

void Channel_Switch::read_new_raw_signal(unsigned long channel_input){
	_last_channel_input = _new_channel_input;
	_new_channel_input = channel_input;
}