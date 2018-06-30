#ifndef __Cyc_array_6DoF__
#define __Cyc_array_6DoF__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug_def.h"
#include "general_defs.h"

#ifdef DEBUG_FUNC_FLOW_CYCLIC_ARRAY_
	#include <i2c_t3.h> // needed to use serial while debugging
#endif

class Cyc_array_6DoF {
private:
	float _array[CYC_ARRAY_SIZE];
	int _front;
	int _itemCount;

public:
	Cyc_array_6DoF();
	float peek();
	void get_cyc_array(float* get_array);
	float get_cyc_array_single(int i);
	bool isEmpty();
	bool isFull();
	void insert(float data);
};

#endif