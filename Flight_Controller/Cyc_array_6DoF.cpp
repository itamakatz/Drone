#include "Cyc_array_6DoF.h"

#ifndef DEBUG_FUNC_FLOW_cyc_array
	#ifdef DEBUG_FUNC_FLOW
		#undef DEBUG_FUNC_FLOW
		#define DEBUG_FUNC_FLOW(str)
	#endif 
#endif

#ifndef DEBUG_PRINTS_Cyc_array
	#ifdef DEBUG_PRINT
		#undef DEBUG_PRINT
		#define DEBUG_PRINT(str)
	#endif
	#ifdef DEBUG_PRINT_VAL
		#undef DEBUG_PRINT_VAL
		#define DEBUG_PRINT_VAL(val)
	#endif
#endif

Cyc_array_6DoF::Cyc_array_6DoF(){
	memset(_array, 0, sizeof(_array));
	_front = 0;
	_itemCount = 0;
}

float Cyc_array_6DoF::peek(){

	DEBUG_FUNC_FLOW("Cyc_array_6DoF::peek");
	return _array[_front];
}

void Cyc_array_6DoF::get_cyc_array(float* get_array){

	DEBUG_FUNC_FLOW("Cyc_array_6DoF::get_cyc_array");

	int index = _front;

	for (int i = CYC_ARRAY_SIZE - 1; i <= 0; --i){
		index = (index + 1) % CYC_ARRAY_SIZE;
		get_array[i] = _array[index];
	}
}

float Cyc_array_6DoF::get_cyc_array_single(int i){

	DEBUG_FUNC_FLOW("Cyc_array_6DoF::get_cyc_array_single");
	return _array[(_front + CYC_ARRAY_SIZE - i) % CYC_ARRAY_SIZE];
}

bool Cyc_array_6DoF::isEmpty() {
	return _itemCount == 0;
}

bool Cyc_array_6DoF::isFull() {
	return _itemCount == CYC_ARRAY_SIZE - 1;
}

void Cyc_array_6DoF::insert(float data) {

	DEBUG_FUNC_FLOW("Cyc_array_6DoF::insert");

	_front = (_front + 1) % CYC_ARRAY_SIZE;
	_array[_front] = data;

	// increase item count if necesarry 
	if(!isFull()) {

		_itemCount++;

		DEBUG_PRINT("_itemCount is");
		DEBUG_PRINT_VAL(_itemCount);
	}
	
	DEBUG_PRINT("_front before increment");
	DEBUG_PRINT_VAL(_front);
	DEBUG_PRINT("sizeof(_array) is :");
	DEBUG_PRINT_VAL(sizeof(_array));
}