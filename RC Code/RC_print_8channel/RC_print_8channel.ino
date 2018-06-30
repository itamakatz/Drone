#include <Metro.h>

// pins
#define LED_PIN 13
#define CHECK_SIGNAL_OUT 22
#define OUTPUT_PIN 23

// PWM
#define PWM_BIT_RESOLUTION 16
#define PWM_FREQUENCY 915.527 // for 180Mhz CPU
#define MIN_PWM_VALUE 0
#define MAX_PWM_VALUE 65535

// metro
#define METRO_BIG_NUM 500000
#define METRO_PRINT 100

// channels
#define NUM_OF_CHANNELS 8
#define PULE_IN_TIMEOUT 25000 // pulseIn - read pwm


// channel variables
uint8_t channel_pins[NUM_OF_CHANNELS] = {2, 3, 4, 5, 6, 7, 8, 9};
size_t channel_input[NUM_OF_CHANNELS];

// bools
bool led_state = HIGH;

// signal variables
int send_signal = 0;
int check_send_signal = 0;

// metro
Metro print_metro = Metro(METRO_PRINT);

void setup() {

	Serial.begin(115200);

	pinMode(LED_PIN, OUTPUT);
	pinMode(OUTPUT_PIN, OUTPUT);
	pinMode(CHECK_SIGNAL_OUT, INPUT);

	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		pinMode(channel_pins[i], INPUT);
	}

}

void loop() {

	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		channel_input[i] = pulseIn(channel_pins[i], HIGH, PULE_IN_TIMEOUT);
	}
	
	analogWrite(OUTPUT_PIN, channel_input[i]);

	check_metros(); 
}

void check_metros(){

	if (print_metro.check()) {

		check_send_signal = pulseIn(CHECK_SIGNAL_OUT, HIGH, PULE_IN_TIMEOUT);

		Serial.println("check_send_signal: " + String(check_send_signal));

		for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
			Serial.println("Channel " + String(i + 1) +": " + String(channel_input[i]));
		}

		Serial.println();

		if (led_state == HIGH)  { 
			led_state = LOW;
		} else {
			led_state = HIGH;
		}
		
		digitalWriteFast(LED_PIN, led_state);

		print_metro.interval(METRO_PRINT);
	}	
}