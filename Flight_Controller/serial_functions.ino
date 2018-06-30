void print_serial(){

	Serial.print(F("angles_Euler: "));
	for (int i = 0; i < 3; ++i){
		Serial.print(angles_Euler[i]);	
		Serial.print(F(", "));
	}

	Serial.println();

	Serial.print(F("angles_Euler_average: "));
	for (int i = 0; i < 3; ++i){
		Serial.print(angles_Euler_average[i]);	
		Serial.print(F(", "));
	}

	Serial.println();

	Serial.println("Signal on Yellow Wire is: " + String(pulseIn(CHECK_SIGNAL_OUT, HIGH, PULSE_IN_TIMEOUT)));

	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		Serial.print("Channel " + String(i + 1) + ": " + String(throttle_channels[i].get_new_channel_input()));
		Serial.print("Channel Difference " + String(i + 1) + ": " + String(throttle_channels[i].get_channel_difference()));
		if (i < NUM_OF_MOTORS) {
			Serial.println(+ ", min: " + String(all_motors[i].get_min_input_signal()) + ", max: " + String(all_motors[i].get_max_input_signal()));
		} else {
			Serial.println();
		}
	}

	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		Serial.print("Motor " + String(i + 1) + ": " + String(all_motors[i].get_motor_speed()));
		Serial.println(", Pin Number: " + String(all_motors[i].get_motor_pin()));
	}
	
	for (int i = 0; i < 3; ++i) {
		Serial.print("target_angles:: " + String(target_angles[i]));
	}

	Serial.println("run State: " + String(run));

	Serial.println("rc_on State: " + String(rc_on));
	
	// Serial.print(F("Number Entered: "));

	Serial.println();
}


#ifdef SERIAL_INPUT_ENABLE

void check_key(){

	DEBUG_FUNC_FLOW("check_key()");

	if (Serial.available() > 0) {

		DEBUG_FUNC_FLOW("check_key() - after if (Serial.available() > 0)");
		
		// read ascii char and convert to int representation
		int incoming_serial = Serial.read() - '0';
		
		DEBUG_PRINT("check_key() - incoming_serial is ");
		DEBUG_PRINT_VAL(incoming_serial);

		switch (incoming_serial) {
			case 1:
				s6DoF_object.calibrate();
				Serial.println(F("Gyro calibrated"));
				break;
			case 2:
				s6DoF_object.set_zero();
				Serial.println(F("Calibrated values to zero"));
				break;
			case 3:
				s6DoF_object.sixDOF_setup((float)0.1);
				Serial.println(F("Run sixDOF_setup again"));
				break;
			default:
				Serial.println(F("Error - input key not legal"));
		}
	}

	// if (Serial.available() > 0) {

	// 	// read ascii char and convert to int representation
	// 	int incoming_serial = Serial.read() - '0';
	// 	while(Serial.available() > 0){
	// 		incoming_serial = incoming_serial * 10 + int(Serial.read() - '0');
	// 	}
	// 	Serial.println("Number Entered:" + String(incoming_serial));
	// }
}
#endif