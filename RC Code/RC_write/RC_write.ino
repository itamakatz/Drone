#include <PWMServo.h>

int LED_PIN = 13;      // select the pin for the LED
int SIGNAL_PIN = 35;
int DELAY_LED = 100;  // variable to store the value coming from the sensor
int DELAY_LOOP = 300;  // variable to store the value coming from the sensor

PWMServo myservo;  // create servo object to control a servo

int incoming_num = 0;

void setup() {
	Serial.begin(115200);
	myservo.attach(SIGNAL_PIN);         // attaches the servo on pin 9 to the servo object
	pinMode(LED_PIN, OUTPUT);  
	//myservo.attach(SIGNAL_PIN, 1000, 2000); // some motors need min/max setting
}

void loop() {
	// val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
	// val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180)

	check_key();

	myservo.write(incoming_num);                  // sets the servo position according to the scaled value
// analogWrite
	digitalWrite(LED_PIN, HIGH);  
	delay(DELAY_LED);          
	digitalWrite(LED_PIN, LOW);  

	delay(DELAY_LOOP);                           // waits for the servo to get there
}

void check_key(){

	if (Serial.available() > 0) {

		// read ascii char and convert to int representation
		incoming_num = Serial.read() - '0';
		while(Serial.available() > 0){
			incoming_num = incoming_num * 10 + int(Serial.read() - '0');
		}

		Serial.print(F("Number Entered: "));
		Serial.println(incoming_num);
	} else{
		Serial.println(F("Please enter number"));
	}
}