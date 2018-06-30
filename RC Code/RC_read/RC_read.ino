/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */

int LED_PIN = 13;      // select the pin for the LED
int DELAY_LOOP = 300;  // variable to store the value coming from the sensor
int DELAY_LED = 100;  // variable to store the value coming from the sensor
 
int CH1 = 5;
int CH2 = 6;
int CH3 = 7;

int TIMEOUT = 25000;

unsigned long ch1; // Here's where we'll keep our channel values
unsigned long ch2;
unsigned long ch3;

void setup() {

  pinMode(LED_PIN, OUTPUT);  

  pinMode(CH1, INPUT); // Set our input pins as such
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);

  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  ch1 = pulseIn(CH1, HIGH, TIMEOUT); // Read the pulse width of 
  ch2 = pulseIn(CH2, HIGH, TIMEOUT); // each channel
  ch3 = pulseIn(CH3, HIGH, TIMEOUT);

  Serial.print("Channel 1:"); // Print the value of 
  Serial.println(ch1);        // each channel

  Serial.print("Channel 2:");
  Serial.println(ch2);

  Serial.print("Channel 3:");
  Serial.println(ch3);

  digitalWrite(LED_PIN, HIGH);  
  delay(DELAY_LED);          
  digitalWrite(LED_PIN, LOW);   

  delay(DELAY_LOOP);  
}