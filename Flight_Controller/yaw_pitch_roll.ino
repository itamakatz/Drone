void yaw(long move_amount){


	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		if(all_motors[i].get_motor_spin == Motor_spin_dir::CW_Spin){
			all_motors[i].set_motor_speed(all_motors[i].get_motor_speed() - move_amount);
		} else{
			all_motors[i].set_motor_speed(all_motors[i].get_motor_speed() + move_amount);
		}
	}

	// all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() + move_amount);
	// all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() + move_amount);

	// all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() - move_amount);
	// all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() - move_amount);

}

void pitch(long move_amount){

	all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + move_amount);
	all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() + move_amount);

	all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() - move_amount);
	all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() - move_amount);

}

void roll(long move_amount){
	
	all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + move_amount);
	all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() + move_amount);

	all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() - move_amount);
	all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() - move_amount);

}

void altitude(long move_amount){
	
	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
		all_motors[i].set_motor_speed(all_motors[i].get_motor_speed() + move_amount);
	}
	// all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + move_amount);
	// all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() + move_amount);
	// all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() + move_amount);
	// all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() + move_amount);

}