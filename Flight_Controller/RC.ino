

void RC_setup() {

	all_motors[F_R_INDEX] = Motor(motor_pins[F_R_INDEX], Motor_spin_dir::CW_Spin);
	all_motors[B_L_INDEX] = Motor(motor_pins[B_L_INDEX], Motor_spin_dir::CW_Spin);

	all_motors[F_L_INDEX] = Motor(motor_pins[F_L_INDEX], Motor_spin_dir::CCW_Spin);
	all_motors[B_R_INDEX] = Motor(motor_pins[B_R_INDEX], Motor_spin_dir::CCW_Spin);

	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		all_channels[i] = Channel(channel_pins[i]);
	}

	// digital signals
	pinMode(CHECK_SIGNAL_OUT, INPUT);

	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		pinMode(channel_pins[i], INPUT);
	}
}

void RC_loop() {

	// check RC special chanels
	check_channel_state();

/* TODO: change PULSE_IN_TIMEOUT*/

	// read PWM signal from the reciver 
	for (int i = 0; i < NUM_OF_CHANNELS; ++i) {
		all_channels[i].read_new_raw_signal(pulseIn(channel_pins[i], HIGH, PULSE_IN_TIMEOUT));
	}

	if(rc_on){
		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			all_motors[i].set_motor_speed_change(all_channels[i].get_channel_difference());
		}
	}
}

void check_channel_state(){

	// check if RC is off and if so reset channel bounds 
	if (all_channels[CH_3].get_new_channel_input() <= CH_3_LOWER_BOUND) {

		rc_on = false;
		set_target_angles = false;

		for (int i = 0; i < NUM_OF_MOTORS; ++i) {
			all_channels[i].reset_motor_boundries();
		}
		
	} else {
		rc_on = true;
	}

	// check if to output signal to motors  
	if (abs(int(all_channels[CH_A].get_new_channel_input() - CH_A_UP)) < CH_A_THRESHOLD) {
		run = true;
		piezo_notification(Piezo_modes::on);
	} else {
		run = false;
		piezo_notification(Piezo_modes::off);
	}

	if (abs(int(all_channels[CH_B].get_new_channel_input() - CH_B_UP)) < CH_B_THRESHOLD && !target_angles_is_set) {
		set_target_angles = true;
		piezo_notification(Piezo_modes::piezo_set_target_angles);
	}
}