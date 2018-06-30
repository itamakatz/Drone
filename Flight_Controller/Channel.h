#ifndef __CHANNEL__
#define __CHANNEL__

#include "debug_def.h"
#include "general_defs.h"

class Channel {
private:
	uint8_t _pin;
	unsigned long _new_channel_input = 0;
	unsigned long _last_channel_input = 0;
	
public:
	Channel(){}
	Channel(uint8_t pin);
	void read_new_raw_signal(unsigned long channel_input);
	uint8_t get_channel_pin();
	long get_channel_difference();
	unsigned long get_new_channel_input();
	unsigned long get_min_input_signal();
	unsigned long get_max_input_signal();
	void reset_channel_boundries();
};

class Channel_Throttle : public Channel {

}

class Channel_Switch : public Channel{
	
}

class Channel_Dial : public Channel{
}

#endif