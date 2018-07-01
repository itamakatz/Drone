#include "Channel.h"

unsigned long MIN_THROTTLE_OUTPUT = map(BLHEliSuit_MIN_THROTTLE - OFF_THROTTLE_OFFSET,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);
unsigned long MAX_THROTTLE_OUTPUT = map(BLHEliSuit_MAX_THROTTLE,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);

unsigned long Channel_Throttle::_calc_map(unsigned long arg){
	return map(arg, _min_input_signal, _max_input_signal, MIN_THROTTLE_OUTPUT, MAX_THROTTLE_OUTPUT);
}

void Channel_Throttle::reset_channel_boundries(){
	_min_input_signal = MIN_MAX_INPUT_SIGNAL;
	_max_input_signal = MIN_MAX_INPUT_SIGNAL;
}

long Channel_Throttle::calc_channel_change(){
	
	if (ch_type == Channel_Types::Throttle_Returning && abs(_new_channel_input - _middle_value) > CHANNEL_THRESHOLD) {
		return (_calc_map(_new_channel_input) - _calc_map(_middle_value));		/* code */
	} else if(ch_type == Channel_Types::Throttle_Fixed && abs(_new_channel_input - _last_channel_input) > CHANNEL_THRESHOLD) {
		return (_calc_map(_new_channel_input) - _calc_map(_min_input_signal));
	}
		
	return 0;
}

void Channel_Throttle::set_middle_value(unsigned long middle_value) {
	_middle_value = middle_value;
}

void Channel_Throttle::read_new_raw_signal(unsigned long channel_input){
	if (_min_input_signal > channel_input) {
		_min_input_signal = channel_input;
	}
	if (_max_input_signal < channel_input) {
		_max_input_signal = channel_input;
	}

	_last_channel_input = _new_channel_input;
	_new_channel_input = channel_input;
}

void Channel_Switch::read_new_raw_signal(unsigned long channel_input){
	_last_channel_input = _new_channel_input;
	_new_channel_input = channel_input;
}