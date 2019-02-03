#include "s6DoF.h"

#ifndef DEBUG_FUNC_FLOW_sixDOF
	#ifdef DEBUG_FUNC_FLOW
		#undef DEBUG_FUNC_FLOW
		#define DEBUG_FUNC_FLOW(str)
	#endif
#endif

#ifndef DEBUG_PRINT_sixDOF
	#ifdef DEBUG_PRINT_LN
		#undef DEBUG_PRINT_LN
		#define DEBUG_PRINT_LN(str)
	#endif
	#ifdef DEBUG_PRINT
		#undef DEBUG_PRINT
		#define DEBUG_PRINT(str)
	#endif
	#ifdef DEBUG_PRINT_VAL_LN
		#undef DEBUG_PRINT_VAL_LN
		#define DEBUG_PRINT_VAL_LN(val)
	#endif
	#ifdef DEBUG_PRINT_VAL
		#undef DEBUG_PRINT_VAL
		#define DEBUG_PRINT_VAL(val)
	#endif
#endif

void s6DoF::sixDOF_setup() {
// void s6DoF::sixDOF_setup(float alpha) {

	DEBUG_FUNC_FLOW("s6DoF::sixDOF_setup");

	delay(INITIAL_DELAY_sixDOF);

	// memset(_average, 0, sizeof(_average));
	// memset(_average_zero_offset, 0, sizeof(_average_zero_offset));

	memset(_angles_Euler, 0, sizeof(_angles_Euler));
	memset(_angles_Euler_zero_offset, 0, sizeof(_angles_Euler_zero_offset));

	// memset(_c_array, 0, sizeof(_c_array));

	// _alpha = alpha;

	// for (int a_i = 0; a_i < 3; ++a_i) {
	// 	_c_array[a_i] = Cyc_array_6DoF();
	// }

	_IMU_controller = IMU_Controller();
	_IMU_controller.init();
	// _init_samples();
}

// void s6DoF::_init_samples(){

// 	DEBUG_FUNC_FLOW("s6DoF::_init_samples");

// 	for (double i = 0.0; i < CYC_ARRAY_SIZE; ++i) {
// 		_IMU_controller.getEuler(_angles_Euler);
// 		for (int a_i = 0; a_i < 3; ++a_i){
// 			_c_array[a_i].insert(_angles_Euler[a_i]);
// 		}
// 	}

// 	for (int a_i = 0; a_i < 3; ++a_i) {
// 		_average[a_i] = _angles_Euler[a_i];
// 	}
// }

void s6DoF::sixDOF_loop() { 

	DEBUG_FUNC_FLOW("s6DoF::sixDOF_loop");

	_IMU_controller.getEuler(_angles_Euler);

	DEBUG_FUNC_FLOW("s6DoF::sixDOF_loop - after getEuler");

	// for (int a_i = 0; a_i < 3; ++a_i) {
	// 	_c_array[a_i].insert(_angles_Euler[a_i]);
	// }

	// DEBUG_FUNC_FLOW("s6DoF::sixDOF_loop - after insert");

	// _update_average();

	// DEBUG_FUNC_FLOW("s6DoF::sixDOF_loop - after _update_average");
}

// void s6DoF::_update_average(){

// 	DEBUG_FUNC_FLOW("s6DoF::_update_average");

// 	for (int a_i = 0; a_i < 3; ++a_i) {
// 		// since the exponential window is recursive, set the first average value as an initial condition
// 		_average[a_i] = _c_array[a_i].get_cyc_array_single(0);

// 		for (int elem_index = 0; elem_index < CYC_ARRAY_SIZE; ++elem_index){
// 			_average[a_i] = _alpha * _average[a_i] + (1 - _alpha) * _c_array[a_i].get_cyc_array_single(elem_index);
// 		}
// 	}
// }

void s6DoF::get_angles(float* angles_Euler) { 

	DEBUG_FUNC_FLOW("s6DoF::get_angles");

	// _IMU_controller.getQ(q);
	// serialPrintFloatArr(q, 4);

	for (int a_i = 0; a_i < 3; ++a_i) {
		angles_Euler[a_i] = _angles_Euler[a_i] - _angles_Euler_zero_offset[a_i];
	}

	#ifdef DEBUG_PRINT_sixDOF

		DEBUG_PRINT_LN("s6DoF - _angles_Euler: ");
		for (int a_i = 0; a_i < 3; ++a_i){
			DEBUG_PRINT_VAL(_angles_Euler[a_i]);
			DEBUG_PRINT(", ");
		}

		DEBUG_PRINT_LN("");

		DEBUG_PRINT_LN("s6DoF - angles_Euler: ");
		for (int a_i = 0; a_i < 3; ++a_i){
			DEBUG_PRINT_VAL(angles_Euler[a_i]);	
			DEBUG_PRINT(", ");
		}

		DEBUG_PRINT_LN("");
	#endif
}

// void s6DoF::get_average(float* angles_average){
	
// 	DEBUG_FUNC_FLOW("s6DoF::get_average");

// 	for (int a_i = 0; a_i < 3; ++a_i) {
// 		angles_average[a_i] = _average[a_i] - _average_zero_offset[a_i];
// 	}

// 	#ifdef DEBUG_PRINT_sixDOF

// 		DEBUG_PRINT_LN("s6DoF - _average: ");
// 		for (int a_i = 0; a_i < 3; ++a_i){
// 			Serial.print(_average[a_i]);	
// 			Serial.print(F(", "));
// 		}

// 		Serial.println();

// 		DEBUG_PRINT_LN("s6DoF - angles_average: ");
// 		for (int a_i = 0; a_i < 3; ++a_i){
// 			Serial.print(angles_average[a_i]);	
// 			Serial.print(F(", "));
// 		}

// 		Serial.println();
// 	#endif	
// }

void s6DoF::calibrate(){

	DEBUG_FUNC_FLOW("s6DoF::calibrate");

	_IMU_controller.gyro.zeroCalibrate(128,5);
	// for (int a_i = 0; a_i < 3; ++a_i) {
	// 	_average[a_i] = 0.0;
	// }
	
	// _init_samples();
}

void s6DoF::set_zero(){
	for (int a_i = 0; a_i < 3; ++a_i) {
		// _average_zero_offset[a_i] = _average[a_i];
		_angles_Euler_zero_offset[a_i] = _angles_Euler[a_i];
	}
}