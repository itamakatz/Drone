#ifndef __CHANNEL__
#define __CHANNEL__

#include "debug_def.h"
#include "general_defs.h"

class Channel {
protected:
	uint8_t _pin;
	unsigned long _new_channel_input = 0;
	unsigned long _last_channel_input = 0;
	
public:
	Channel_Types ch_type;

	Channel(Channel_Types set_ch_type): ch_type(set_ch_type) {}
	Channel(uint8_t pin);
	uint8_t get_channel_pin();
	unsigned long get_new_channel_input();

	virtual void read_new_raw_signal(unsigned long channel_input) = 0;

	long get_channel_difference();


};

class Channel_Throttle : public Channel {
private:
	unsigned long _min_input_signal = 0;
	unsigned long _max_input_signal = 0;
public:
	Channel_Throttle(Channel_Types set_ch_type): Channel(set_ch_type) {}
	void read_new_raw_signal(unsigned long channel_input);
	unsigned long get_min_input_signal();
	unsigned long get_max_input_signal();
	void reset_channel_boundries();
}

class Channel_Returning_Throttle : public Channel_Throttle {
public:
	Channel_Returning_Throttle(): Channel_Throttle(Channel_Types::Throttle_Returning) {}
}

class Channel_Fixed_Throttle : public Channel_Throttle{
public:
	Channel_Fixed_Throttle(): Channel_Throttle(Channel_Types::Throttle_Fixed) {}
}

class Channel_Switch : public Channel{
public:
	Channel_Types ch_type = Channel_Types::Switch_Channel;
}

#endif