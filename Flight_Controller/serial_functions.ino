void print_serial()
{

	PRINT_F_STRING_LN("angles_Euler: ");
	for (int i = 0; i < 3; ++i)
	{
		Serial.print(angles_Euler[i]);
		Serial.print(F(", "));
	}

	// Serial.println();

	// Serial.print(F("angles_Euler_average: "));
	// for (int i = 0; i < 3; ++i){
	// 	Serial.print(angles_Euler_average[i]);
	// 	Serial.print(F(", "));
	// }

	Serial.println();

	Serial.println("Signal on Yellow Wire is: " + String(pulseIn(CHECK_SIGNAL_OUT, HIGH, PULSE_IN_TIMEOUT)));
	Serial.println("Sensitivity is: " + String(sensitivity));
	Serial.println("MIN_THROTTLE_OUTPUT is: " + String(MIN_THROTTLE_OUTPUT) + ", MAX_THROTTLE_OUTPUT is: " + String(MAX_THROTTLE_OUTPUT));

	for (int i = 0; i < NUM_OF_TRHROTTLE_CHANNELS; ++i)
	{
		Serial.print("Channel " + String(i + 1) + ": " + String(throttle_channels[i].get_new_channel_input()));
		Serial.print(", Channel Difference " + String(i + 1) + ": " + String(throttle_channels[i].calc_channel_change()));
		// Serial.print(", Channel Current " + String(i + 1) + ": " + String(throttle_channels[i].get_channel_current()));		
		Serial.print(+", min: " + String(throttle_channels[i].get_min_input_signal()) + ", max: " + String(throttle_channels[i].get_max_input_signal()));

		if (throttle_channels[i].ch_type == Channel_Types::Throttle_Returning)
		{
			Serial.print(+", middle: " + String(throttle_channels[i].get_middle_value()));
		}

		Serial.println();
	}

	Serial.println("Channel (Switch) A: " + String(switch_channels[CH_A].get_new_channel_input()));
	Serial.println("Channel (Switch) B: " + String(switch_channels[CH_B].get_new_channel_input()));

	for (int i = 0; i < NUM_OF_MOTORS; ++i)
	{
		Serial.print("Motor " + String(i + 1) + ": " + String(all_motors[i].get_motor_speed()));
		Serial.println(", Pin Number: " + String(all_motors[i].get_motor_pin()));
	}

	// for (int i = 0; i < 3; ++i) {
	// 	Serial.print("target_angles:: " + String(target_angles[i]));
	// }

	Serial.println("run State: " + String(run));

	Serial.println("rc_on State: " + String(rc_on));

	// Serial.print(F("Number Entered: "));

	Serial.println();
}

#ifdef SERIAL_INPUT_ENABLE

void serialEvent()
{

	DEBUG_FUNC_FLOW("serialEvent()");

	if (Serial.available() > 0)
	{

		DEBUG_FUNC_FLOW("serialEvent() - after if (Serial.available() > 0)");

		char incoming_serial_char = Serial.read();

		DEBUG_PRINT_LN("serialEvent() - incoming_serial is ");
		DEBUG_PRINT_VAL_LN(incoming_serial);

		switch (incoming_serial_char)
		{
		case 'H':
		case 'h':
			PRINT_F_STRING_LN("1 - Gyro Calicration");
			PRINT_F_STRING_LN("2 - Calibrate values to zero");
			PRINT_F_STRING_LN("3 - Run sixDOF_setup again");
			return;

		case 'm':
		case 'M':

			if (Serial.available() > 0)
			{

				// read ascii char and convert to int representation
				int incoming_serial = Serial.read() - '0';
				while (Serial.available() > 0)
				{
					incoming_serial = incoming_serial * 10 + int(Serial.read() - '0');
				}
				Serial.println("Number Entered:" + String(incoming_serial));
			}
			return;
		case 'p':
		case 'P':
			print_feedback = !print_feedback;
			PRINT_F_STRING("Toggled printing feedback to: ");
			Serial.println(String(print_feedback));
			return;
		}

		// read ascii char and convert to int representation
		int incoming_serial_val = incoming_serial_char - '0';

		switch (incoming_serial_val)
		{
		case 1:
			s6DoF_object.calibrate();
			PRINT_F_STRING_LN("Gyro calibrated");
			break;
		case 2:
			s6DoF_object.set_zero();
			PRINT_F_STRING_LN("Calibrated values to zero");
			break;
		case 3:
			// s6DoF_object.sixDOF_setup((float)0.1);
			s6DoF_object.sixDOF_setup();
			PRINT_F_STRING_LN("Run sixDOF_setup again");
			break;
		default:
			DEBUG_PRINT_LN("Error - input key not legal");
		}
	}
}
#endif