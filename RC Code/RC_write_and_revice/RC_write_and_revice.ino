#include <Metro.h>
#include "SimpleFIFO.h"

// addendum pins
#define LED_PIN 13
#define CHECK_SIGNAL_OUT 36

// ANALOGWRITE
#define ANALOGWRITE_BIT_RESOLUTION 16
#define ANALOGWRITE_FREQUENCY 915.527 // for 180MHz CPU
#define MIN_ANALOGWRITE_VALUE 0
#define MAX_ANALOGWRITE_VALUE 65535

// PWM
#define MIN_POSSIBLE_OUTPUT 0
#define MAX_POSSIBLE_OUTPUT 2048
#define BLHEliSuit_MIN_THROTTLE 1020
#define BLHEliSuit_MAX_THROTTLE 2000
#define OFF_THROTTLE_OFFSET 50
unsigned long min_throttle_output = map(BLHEliSuit_MIN_THROTTLE - OFF_THROTTLE_OFFSET,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);
unsigned long max_throttle_output = map(BLHEliSuit_MAX_THROTTLE,  MIN_POSSIBLE_OUTPUT, MAX_POSSIBLE_OUTPUT, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);

// delays
#define SETUP_LOOP 1500
#define DELAY_LOOP 300

// piezo
#define METRO_PIEZO_INTERVAL 100
#define PIEZO_PIN 35
#define PIEZO_RESONANCE 250 // (from 2040?)

// metro
#define METRO_PRINT_INTERVAL 100
#define METRO_CHECK_SERIAL_INTERVAL 1500

// channels
#define NUM_OF_CHANNELS 8
#define PULSE_IN_TIMEOUT 25000 // pulseIn - read pwm

#define CH_3 2
#define CH_3_LOWER_BOUND 900

#define CH_A 6
#define CH_A_UP 997
#define CH_A_OFF 1996
#define CH_A_THRESHOLD 50

#define CH_B 4
#define CH_B_ON 997
#define CH_B_MIDDLE 1497
#define CH_B_OFF 1996
#define CH_B_THRESHOLD 50

// enable or disable serial prints
// #define SERIAL_INPUT_ENABLE

// channel variables
unsigned long channel_input[NUM_OF_CHANNELS];
uint8_t channel_pins[NUM_OF_CHANNELS] = {2, 3, 4, 5, 6, 7, 8, 9};

// motor variables
#define NUM_OF_MOTORS 4
unsigned long min_input_signal[NUM_OF_MOTORS];
unsigned long max_input_signal[NUM_OF_MOTORS];
unsigned long MIN_MAX_INPUT_SIGNAL[2] = {1500, 1500};

unsigned long motor_control_output[NUM_OF_MOTORS];
uint8_t motor_pins[NUM_OF_MOTORS] = {20, 21, 22, 23};

// bools
bool rc_on = false;
bool run = false;
bool led_state = HIGH;

// signal variables
unsigned long check_send_signal = 0;
int incoming_serial = 0;

// piezo and metro
int piezo_tone = map(PIEZO_RESONANCE, 0, 1024, MIN_ANALOGWRITE_VALUE, MAX_ANALOGWRITE_VALUE);
enum Piezo_modes { none, on, off };
Piezo_modes last_mode = none;
SimpleFIFO<int,10> piezo_fifo;

Metro print_metro = Metro(METRO_PRINT_INTERVAL);
Metro piezo_metro = Metro(METRO_PIEZO_INTERVAL);

#ifdef SERIAL_INPUT_ENABLE
	Metro check_serial_metro = Metro(METRO_CHECK_SERIAL_INTERVAL);	
#endif

void setup() {

// possibly put analogWriteResolution before analogWrite

	// set all motor outputs to 0  
	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		analogWrite(motor_pins[i], 0);
	}

	memset(channel_input, 0, sizeof(channel_input));
	memset(min_input_signal, 0, sizeof(min_input_signal));
	memset(max_input_signal, 0, sizeof(max_input_signal));
	memset(motor_control_output, 0, sizeof(motor_control_output));

	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		min_input_signal[i] = MIN_MAX_INPUT_SIGNAL[0];
		max_input_signal[i] = MIN_MAX_INPUT_SIGNAL[1];
	}

	Serial.begin(115200);

	// digital signals
	pinMode(LED_PIN, OUTPUT);
	pinMode(CHECK_SIGNAL_OUT, INPUT);

	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		pinMode(channel_pins[i], INPUT);
	}

	// analog signals
	analogWriteResolution(ANALOGWRITE_BIT_RESOLUTION);


/* - maybe not needed since analogWriteFrequency is called on pin PIEZO_PIN and it needs to be called only once
	// set output PWM frequency of all the motors
	// for (int i = 0; i < NUM_OF_MOTORS; ++i) {
	// 	analogWriteFrequency(motor_pins[i], ANALOGWRITE_FREQUENCY);
	// }
*/
	// set output PWM frequency of the piezo
	analogWriteFrequency(PIEZO_PIN, ANALOGWRITE_FREQUENCY);


	delay(SETUP_LOOP);
	Serial.println("piezo_tone - " + String(piezo_tone));
	Serial.println("MIN_ANALOGWRITE_VALUE - " + String(MIN_ANALOGWRITE_VALUE));
	Serial.println("MAX_ANALOGWRITE_VALUE - " + String(MAX_ANALOGWRITE_VALUE));
}

void loop() {

	// check RC special chanels
	check_channel_state();

/* TODO: change PULSE_IN_TIMEOUT*/

	// read PWM signal from the reciver 
	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		channel_input[i] = pulseIn(channel_pins[i], HIGH, PULSE_IN_TIMEOUT);
	}

	// before using the map function, verify the min/max values are indeed bounds  
	if(rc_on){
		for (int i = 0; i < NUM_OF_MOTORS; ++i) // NUM_OF_MOTORS since only those channels are dynamic
		{
			if (min_input_signal[i] > channel_input[i]) {
				min_input_signal[i] = channel_input[i];
			}
			if (max_input_signal[i] < channel_input[i]) {
				max_input_signal[i] = channel_input[i];
			}
		}
	}

	// calculate corresponding output signal of the motors  
	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		motor_control_output[i] = map(channel_input[i], min_input_signal[i], max_input_signal[i], min_throttle_output, max_throttle_output);
	}

	if (run) {
		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			analogWrite(motor_pins[i], motor_control_output[CH_3]);
		}
	} else{
		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			analogWrite(motor_pins[i], 0);
		}
	}

	check_metros(); 
}

void check_metros(){

#ifdef SERIAL_INPUT_ENABLE
	// check check_serial_metro
	if (check_serial_metro.check()) {
		
		check_key();
		
		check_serial_metro = Metro(METRO_CHECK_SERIAL_INTERVAL);
	}
#endif

	// check print_metro
	if (print_metro.check()) {

		check_send_signal = pulseIn(CHECK_SIGNAL_OUT, HIGH, PULSE_IN_TIMEOUT);

		Serial.println("check_send_signal: " + String(check_send_signal));

		for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
			Serial.print("Channel " + String(i + 1) + ": " + String(channel_input[i]));
			if (i < NUM_OF_MOTORS) {
				Serial.println(+ ", min: " + String(min_input_signal[i]) + ", max: " + String(max_input_signal[i]));
			} else {
				Serial.println();
			}
		}

		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			Serial.println("Motor " + String(i + 1) + ": " + String(motor_control_output[i]));
		}

#ifdef SERIAL_INPUT_ENABLE
		Serial.println("incoming_serial: " + String(incoming_serial));
#endif
				
		Serial.println("run State: " + String(run));

		Serial.println("rc_on State: " + String(rc_on));
		
		// Serial.print(F("Number Entered: "));

		Serial.println();

		if (led_state == HIGH)  { 
			led_state = LOW;
		} else {
			led_state = HIGH;
		}
		
		digitalWriteFast(LED_PIN, led_state);

		print_metro.interval(METRO_PRINT_INTERVAL);
	}

	// check piezo_metro
	if (piezo_metro.check() && piezo_fifo.count() > 0) {
		if (piezo_fifo.peek() > 0){
			analogWrite(PIEZO_PIN, piezo_tone);
			Serial.println("piezo_fifo.peek() = " + String(piezo_fifo.peek()));
			piezo_metro.interval(piezo_fifo.dequeue());
		} else {
			analogWrite(PIEZO_PIN, 0);
			piezo_metro.interval(-1 * piezo_fifo.dequeue());
		}
	}
}

void check_channel_state(){

	if (channel_input[CH_3] <= CH_3_LOWER_BOUND) {
		rc_on = false;
		memset(max_input_signal, 0, sizeof(max_input_signal));
		memset(motor_control_output, 0, sizeof(motor_control_output));

		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			min_input_signal[i] = MIN_MAX_INPUT_SIGNAL[0];
			max_input_signal[i] = MIN_MAX_INPUT_SIGNAL[1];
		}
	} else {
		rc_on = true;
	}

	if (abs(int(channel_input[CH_A] - CH_A_UP)) < CH_A_THRESHOLD) {
		run = true;
		piezo_notification(Piezo_modes::on);
	} else {
		run = false;
		piezo_notification(Piezo_modes::off);
	}
}

void piezo_notification(Piezo_modes mode){

#define PIEZZO_SHORT_DELAY 200
#define PIEZZO_VERY_LONG_DELAY 1000
	
	if (last_mode != mode) {
		switch (mode) {
			case Piezo_modes::on:
				piezo_fifo.flush();
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);				
				piezo_fifo.enqueue(PIEZZO_VERY_LONG_DELAY);
				piezo_fifo.enqueue(-1);
				break;
			case Piezo_modes::off:
				piezo_fifo.flush();
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1);
				break;
			default:
				break;
		}
	}

	last_mode = mode;

	// analogWrite(PIEZO_PIN, 0);
}

#ifdef SERIAL_INPUT_ENABLE
void check_key(){

	if (Serial.available() > 0) {

		// read ascii char and convert to int representation
		incoming_serial = Serial.read() - '0';
		while(Serial.available() > 0){
			incoming_serial = incoming_serial * 10 + int(Serial.read() - '0');
		}
		Serial.println("Number Entered:" + String(incoming_serial));
	}

	if (Serial.available() > 0) {
		incoming_serial = int(Serial.read() - '0');
		switch (incoming_serial){
			case 1:
				rc_on = true;
				piezo_notification();
				break;
			case 2:
				run = true;
				break;		
			case 3:
				run = false;
				break;	
		}
	}
}
#endif