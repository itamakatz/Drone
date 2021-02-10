void set_absolute_motors_speed(long c_altitude, long c_yaw, long c_roll, long c_pitch){
	
	long new_speeds[NUM_OF_MOTORS];

	// if(c_altitude < 300){
	// 	for (int i = 0; i < NUM_OF_MOTORS; ++i) {
	// 		all_motors[i].set_absolute_speed(0);
	// 	}
	// }

	// altitude
	for (int i = 0; i < NUM_OF_MOTORS; i++) { new_speeds[i] = /*32639*/ + c_altitude; }

	// // yaw
	// for (int i = 0; i < NUM_OF_MOTORS; i++) { 
	// 	if(all_motors[i].get_spin() == Motor_spin_dir::CW_Spin){ new_speeds[i] -= c_yaw; }
	// 	else{ new_speeds[i] += c_yaw; }
	// }

	// // pitch
	// new_speeds[F_R_INDEX] += c_pitch;
	// new_speeds[B_R_INDEX] += c_pitch;

	// new_speeds[B_L_INDEX] -= c_pitch;
	// new_speeds[F_L_INDEX] -= c_pitch;

	// // roll
	// new_speeds[F_R_INDEX] += c_roll;
	// new_speeds[F_L_INDEX] += c_roll;

	// new_speeds[B_L_INDEX] -= c_roll;
	// new_speeds[B_R_INDEX] -= c_roll;

	// update motors
	for (int i = 0; i < NUM_OF_MOTORS; ++i) { all_motors[i].set_absolute_speed(new_speeds[i]); }
}