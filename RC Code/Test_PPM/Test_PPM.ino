code not working....

// #include <PulsePosition.h>

// // Simple loopback test: create 1 output to transmit
// // test pulses, and 1 input to receive the pulses
// PulsePositionOutput myOut;
// PulsePositionInput myIn;

// #define CHECK_SIGNAL_OUT 2	
// #define PULE_IN_TIMEOUT 2500

// void setup() {
// 	Serial.begin(115200);
// 	myOut.begin(9);	// connect pins 9 and 10 together...
// 	myIn.begin(10);
// 	myOut.write(1, 600.03);
// 	myOut.write(2, 1500);
// 	myOut.write(3, 759.24);
// 	// slots 4 and 5 will default to 1500 us
// 	myOut.write(6, 1234.56);

// 	pinMode(CHECK_SIGNAL_OUT, INPUT);

// 	delay(1500);
// 	Serial.print("started");
// }

// int count=0;

// void loop() {
// 	int i, num;

// 	// Serial.println("pulseIn - " + String(pulseIn(CHECK_SIGNAL_OUT, HIGH, PULE_IN_TIMEOUT)));

// 	// Every time new data arrives, simply print it
// 	// to the Arduino Serial Monitor.
// 	num = myIn.available();
// 	Serial.println(num);
// 	if (num > 0) {
// 		Serial.println("im in");
// 		count = count + 1;
// 		Serial.print(count);
// 		Serial.print(" :	");
// 		for (i=1; i <= num; i++) {
// 			float val = myIn.read(i);
// 			Serial.print(val);
// 			Serial.print("	");
// 		}
// 		Serial.println();
// 	}
// 	delay(300);
// }