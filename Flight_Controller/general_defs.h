#ifndef __GENETAL_DEFS__
#define __GENETAL_DEFS__

// ============================== GPIO parameters ================================= //

#define LED_PIN 13
#define CHECK_SIGNAL_OUT 36

// enable or disable serial prints
#define SERIAL_INPUT_ENABLE

// Print Strings
#define PRINT_F_STRING(val) Serial.print(F(val));
#define PRINT_F_STRING_LN(val) Serial.println(F(val));

//  AnalogWrite
#define ANALOGWRITE_BIT_RESOLUTION 16
#define ANALOGWRITE_FREQUENCY 915.527 // for 180MHz CPU
#define MIN_ANALOGWRITE_VALUE 0
#define MAX_ANALOGWRITE_VALUE 65535 

// PWM
#define MIN_POSSIBLE_OUTPUT 0
#define MAX_POSSIBLE_OUTPUT 2048
#define OFF_THROTTLE_OFFSET 50
#define BLHEliSuit_MIN_THROTTLE 1020
#define BLHEliSuit_MAX_THROTTLE 2000

// ============================ Cyclic Array Parameters =========================== //

#define CYC_ARRAY_SIZE 	50
#define sixDOF_ALPHA 	(float)0.01

// ============================== Delays and Metros =============================== //

#define INITIAL_DELAY_sixDOF 			60
#define INITIAL_DELAY_main_ino 			1000

#define CRITICAL_DELAY_LOOP_main_ino 	60

#define METRO_LED_HIGH_INTERVAL 		250 // blincking led 
#define METRO_GENERAL_INTERVAL 			500
#define METRO_LED_LOW_INTERVAL 			1000 // blincking led 
#define METRO_PRINT_INTERVAL 			1000 // print results
#define METRO_BIG_NUM 					50000 // dummy for initialization
#define METRO_CHECK_SERIAL_INTERVAL 	1500

// channels
#define NUM_OF_SWITCH_CHANNELS 2
#define NUM_OF_TRHROTTLE_CHANNELS 6
#define PULSE_IN_TIMEOUT 25000 // pulseIn - read pwm


#define CH_3 2
#define CH_3_LOWER_BOUND 900

#define CH_A 1
#define CH_A_UP 997
#define CH_A_DOWN 1996
#define CH_A_THRESHOLD 50

#define CH_B 0
#define CH_B_UP 997
#define CH_B_MIDDLE 1497
#define CH_B_DOWN 1996
#define CH_B_THRESHOLD 50

#define YAW_CH 3
#define ROLL_CH 0
#define PITCH_CH 1
#define ALTITUDE_CH 2
#define EXTRA_RIGHT_CH					4
#define EXTRA_LEFT_CH					5

#define RETURNING_CHANNEL_THRESHOLD 	50
#define GENERAL_CHANNEL_THRESHOLD		50

enum Channel_Types 	{ Throttle_Fixed, Throttle_Returning, Switch_Channel};

// motor variables
#define NUM_OF_MOTORS 4
#define F_L_INDEX 0
#define F_R_INDEX 1
#define B_R_INDEX 2
#define B_L_INDEX 3
#define MIN_MAX_INPUT_SIGNAL 1500
extern unsigned long MIN_THROTTLE_OUTPUT;
extern unsigned long MAX_THROTTLE_OUTPUT;
extern unsigned long MIN_OFFSET_THROTTLE_OUTPUT;

// piezo
#define PIEZO_PIN 35
#define PIEZO_RESONANCE 250 // (from 2040?)
enum Piezo_modes { none, on, off, set_target_angles, set_sensitivity };
#define PIEZO_TONE map(PIEZO_RESONANCE, 0, 1024, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE)

#define EULER_YAW_INDEX 0
#define EULER_PITCH_INDEX 1
#define EULER_ROLL_INDEX 2

#define SENSITIVITY_LOWEST 0.3
#define SENSITIVITY_HIGHEST 1
#define SENSITIVITY_DEFAULT 0.75

// /* PID variables */
// #define Kp 7
// #define Ki 2
// #define Kd 8

#endif