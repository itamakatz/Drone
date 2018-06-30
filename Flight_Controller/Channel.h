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

	Channel(){}
	Channel(uint8_t pin, Channel_Types set_ch_type): ch_type(set_ch_type) {}
	uint8_t get_channel_pin() {return _pin;}
	unsigned long get_new_channel_input() {return _new_channel_input;}

	virtual void read_new_raw_signal(unsigned long channel_input) = 0;
};

// TODO: add static_cast or dynamic_cast
// B* pB = static_cast<B*>(x);
// pB->myNewMethod();

class Channel_Throttle : public Channel {
private:
	unsigned long _min_input_signal = MIN_MAX_INPUT_SIGNAL;
	unsigned long _max_input_signal = MIN_MAX_INPUT_SIGNAL;
	unsigned long _middle_value = 0;

public:
	Channel_Throttle(): Channel() {}
	Channel_Throttle(uint8_t pin, Channel_Types set_ch_type): Channel(pin, set_ch_type) {}
	unsigned long get_min_input_signal(){return _min_input_signal;}
	unsigned long get_max_input_signal(){return _max_input_signal;}

	void read_new_raw_signal(unsigned long channel_input);

	void reset_channel_boundries();
	long get_channel_difference();

	void set_middle_value(unsigned long middle_value){_middle_value = middle_value;}
	unsigned long get_middle_value(){return _middle_value;}
};

class Channel_Switch : public Channel{
public:
	Channel_Switch(): Channel() {}
	Channel_Switch(uint8_t pin): Channel(pin, Channel_Types::Switch_Channel) {}
	void read_new_raw_signal(unsigned long channel_input);
};

#endif