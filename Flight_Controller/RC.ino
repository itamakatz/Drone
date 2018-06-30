

void RC_setup() {

	all_motors[F_R_INDEX] = Motor(motor_pins[F_R_INDEX], Motor_spin_dir::CW_Spin);
	all_motors[B_L_INDEX] = Motor(motor_pins[B_L_INDEX], Motor_spin_dir::CW_Spin);

	all_motors[F_L_INDEX] = Motor(motor_pins[F_L_INDEX], Motor_spin_dir::CCW_Spin);
	all_motors[B_R_INDEX] = Motor(motor_pins[B_R_INDEX], Motor_spin_dir::CCW_Spin);

	throttle_channels[0] = Channel_Throttle(channel_thrust_pins[0], Channel_Types::Throttle_Fixed);
	throttle_channels[1] = Channel_Throttle(channel_thrust_pins[1], Channel_Types::Throttle_Fixed);
	throttle_channels[3] = Channel_Throttle(channel_thrust_pins[3], Channel_Types::Throttle_Fixed);

	throttle_channels[2] = Channel_Throttle(channel_thrust_pins[2], Channel_Types::Throttle_Returning);
	throttle_channels[4] = Channel_Throttle(channel_thrust_pins[4], Channel_Types::Throttle_Returning);
	throttle_channels[5] = Channel_Throttle(channel_thrust_pins[5], Channel_Types::Throttle_Returning);

	switch_channels[CH_A] = Channel_Switch(channel_switch_pins[CH_A]);
	switch_channels[CH_B] = Channel_Switch(channel_switch_pins[CH_B]);
}

	// digital signals
	pinMode(CHECK_SIGNAL_OUT, INPUT);

	for (int i = 0; i < NUM_OF_TRHROTTLE_CHANNELS; ++i) {
		pinMode(channel_thrust_pins[i], INPUT);
	}

	for (int i = 0; i < NUM_OF_SWITCH_CHANNELS; ++i) {
		pinMode(channel_switch_pins[i], INPUT);
	}
}

void RC_loop() {

	// check RC special chanels
	check_channel_state();

/* TODO: change PULSE_IN_TIMEOUT*/

	// read PWM signal from the reciver 

	for (int i = 0; i < NUM_OF_TRHROTTLE_CHANNELS; ++i) {
		throttle_channels[i].read_new_raw_signal(pulseIn(channel_thrust_pins[i], HIGH, PULSE_IN_TIMEOUT));
	}

	for (int i = 0; i < NUM_OF_SWITCH_CHANNELS; ++i) {
		switch_channels[i].read_new_raw_signal(pulseIn(channel_switch_pins[i], HIGH, PULSE_IN_TIMEOUT));
	}
	
	if(rc_on){
		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			all_motors[i].set_motor_speed_change(throttle_channels[i].get_channel_difference());
		}
	}
}

void check_channel_state(){

	// check if RC is off and if so reset channel bounds 
	if (throttle_channels[CH_3].get_new_channel_input() <= CH_3_LOWER_BOUND) {

		rc_on = false;
		set_target_angles = false;

		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			throttle_channels[i].reset_channel_boundries();
		}
		
	} else {
		rc_on = true;
	}

	// check if to output signal to motors  
	if (abs(int(switch_channels[CH_A].get_new_channel_input() - CH_A_UP)) < CH_A_THRESHOLD) {
		run = true;
		piezo_notification(Piezo_modes::on);
	} else {
		run = false;
		piezo_notification(Piezo_modes::off);
	}

	if (abs(int(switch_channels[CH_B].get_new_channel_input() - CH_B_UP)) < CH_B_THRESHOLD && !target_angles_is_set) {
		set_target_angles = true;
		piezo_notification(Piezo_modes::piezo_set_target_angles);
	}
}