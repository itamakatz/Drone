void yaw(Yaw_dir dir, unsigned long power){

	all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + dir * power);
	all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() + dir * power);

	all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() - dir * power);
	all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() - dir * power);

}

void pitch(Pitch_dir dir, unsigned long power){

	all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + dir * power);
	all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() + dir * power);

	all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() - dir * power);
	all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() - dir * power);

}

void roll(Roll_dir dir, unsigned long power){
	
	all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + dir * power);
	all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() + dir * power);

	all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() - dir * power);
	all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() - dir * power);

}

void up_down(Up_Down_dir dir, unsigned long power){
	
	all_motors[F_R_INDEX].set_motor_speed(all_motors[F_R_INDEX].get_motor_speed() + dir * power);
	all_motors[F_L_INDEX].set_motor_speed(all_motors[F_L_INDEX].get_motor_speed() + dir * power);
	all_motors[B_L_INDEX].set_motor_speed(all_motors[B_L_INDEX].get_motor_speed() + dir * power);
	all_motors[B_R_INDEX].set_motor_speed(all_motors[B_R_INDEX].get_motor_speed() + dir * power);

}