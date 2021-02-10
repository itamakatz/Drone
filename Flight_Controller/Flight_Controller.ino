#include "s6DoF.h"
#include <Metro.h>
#include <i2c_t3.h>
#include "debug_def.h"
#include "general_defs.h"
#include "SimpleFIFO.h"
#include "Motor.h"
#include "Channel.h"

// if not defined, override macro not to print anything
#ifndef DEBUG_FUNC_FLOW_main_ino
#ifdef DEBUG_FUNC_FLOW
#undef DEBUG_FUNC_FLOW
#define DEBUG_FUNC_FLOW(str)
#endif
#endif

#ifndef DEBUG_PRINT_main_ino
#ifdef DEBUG_PRINT_LN
#undef DEBUG_PRINT_LN
#define DEBUG_PRINT_LN(str)
#endif
#ifdef DEBUG_PRINT
#undef DEBUG_PRINT
#define DEBUG_PRINT(str)
#endif
#ifdef DEBUG_PRINT_VAL_LN
#undef DEBUG_PRINT_VAL_LN
#define DEBUG_PRINT_VAL_LN(val)
#endif
#ifdef DEBUG_PRINT_VAL
#undef DEBUG_PRINT_VAL
#define DEBUG_PRINT_VAL(val)
#endif
#endif

uint8_t motor_pins[NUM_OF_MOTORS] = {23, 22, 21, 20};
// uint8_t channel_pins[NUM_OF_CHANNELS] = {2, 3, 4, 5, 6, 7, 8, 9};
// channel number -                        {1, 2, 3, 4, 5, 6, 7, 8};

uint8_t channel_thrust_pins[NUM_OF_TRHROTTLE_CHANNELS] = {2, 3, 4, 5, 7, 9};
uint8_t channel_switch_pins[NUM_OF_SWITCH_CHANNELS] = {6, 8};

float angles_Euler[3] = {0};
// float angles_Euler_average[3] = {0};
s6DoF s6DoF_object = s6DoF();

Piezo_modes last_mode = none;
SimpleFIFO<int, 10> piezo_fifo;

Motor all_motors[NUM_OF_MOTORS];
Channel_Throttle throttle_channels[NUM_OF_TRHROTTLE_CHANNELS];
Channel_Switch switch_channels[NUM_OF_SWITCH_CHANNELS];

bool run = false;
bool rc_on = false;
bool print_feedback = true;
float sensitivity = SENSITIVITY_DEFAULT;

void setup()
{
	// set AnalogWrite resolution
	analogWriteResolution(ANALOGWRITE_BIT_RESOLUTION);

	// CRUCIAL - FIRST THING TO DO: SHUT OFF MOTORS
	for (int i = 0; i < NUM_OF_MOTORS; ++i) { analogWrite(motor_pins[i], 0); }

#ifdef DEBUG_FUNC_FLOW_main_ino
	delay(INITIAL_DELAY_main_ino);
#endif

	Serial.begin(115200);
	Wire.begin();

	// set output PWM frequency of the piezo
	analogWriteFrequency(PIEZO_PIN, ANALOGWRITE_FREQUENCY);

	DEBUG_FUNC_FLOW("setup: after Wire.begin()");

	// s6DoF_object.sixDOF_setup(sixDOF_ALPHA);
	s6DoF_object.sixDOF_setup();
	pinMode(LED_PIN, OUTPUT);
	digitalWriteFast(LED_PIN, HIGH);

	RC_setup();

	DEBUG_FUNC_FLOW("setup: after objects init");
}

void loop()
{
	DEBUG_FUNC_FLOW("loop: beginning");
	check_metros();

	s6DoF_object.sixDOF_loop();
	s6DoF_object.get_angles(&angles_Euler[0]);
	// s6DoF_object.get_average(&angles_Euler_average[0]);

	RC_loop();

	for (int i = 0; i < NUM_OF_MOTORS; ++i) { all_motors[i].set_motor_speed(0); }

	if (run)
	{
		long current_altitude	= throttle_channels[ALTITUDE_CH].calc_channel_change();
		long current_yaw		= throttle_channels[YAW_CH].calc_channel_change();
		long current_roll		= throttle_channels[ROLL_CH].calc_channel_change();
		long current_pitch		= throttle_channels[PITCH_CH].calc_channel_change();
	
		set_absolute_motors_speed(current_altitude, 
								(long)(current_yaw * sensitivity), 
								(long)(current_roll * sensitivity),
								(long)(current_pitch * sensitivity));
		// all_motors[i].set_absolute_speed_change(PIDValue[i]);

		// all_motors[B_R_INDEX].set_absolute_speed(MAX_THROTTLE_OUTPUT);

		// for (int i = 0; i < NUM_OF_MOTORS; ++i) { analogWrite(all_motors[i].get_pin(), all_motors[i].get_speed()); }
	}

	for (int i = 0; i < NUM_OF_MOTORS; ++i) { analogWrite(all_motors[i].get_motor_pin(), all_motors[i].get_motor_speed()); }

	DEBUG_FUNC_FLOW("loop: after updating objects");

	delay(CRITICAL_DELAY_LOOP_main_ino);
}