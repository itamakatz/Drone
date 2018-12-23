#ifndef __DEBUG_DEF__
#define __DEBUG_DEF__

#include <Arduino.h>

// #define DEBUG_VERBOSE
// #define DEBUG

// =========================== Flow Debugging =========================== //

// #define DEBUG_FUNC_FLOW_ALL

// #define DEBUG_FUNC_FLOW_main_ino

// #define DEBUG_FUNC_FLOW_sixDOF

// #define DEBUG_FUNC_FLOW_cyc_array

#ifdef DEBUG_FUNC_FLOW_ALL

	#ifndef DEBUG_FUNC_FLOW_main_ino
		#define DEBUG_FUNC_FLOW_main_ino
	#endif

	#ifndef DEBUG_FUNC_FLOW_sixDOF
		#define DEBUG_FUNC_FLOW_sixDOF
	#endif

	#ifndef DEBUG_FUNC_FLOW_cyc_array
		#define DEBUG_FUNC_FLOW_cyc_array
	#endif

#endif

// =========================== Individual Debugging by Printing =========================== //

// #define DEBUG_PRINT_main_ino

// #define DEBUG_PRINT_sixDOF

// #define DEBUG_PRINTS_Cyc_array


// =========================== Normal Prints =========================== //

// #define ENABLE_NORMAL_PRINTS

// =========================== Printing Macros =========================== //

#ifdef DEBUG_VERBOSE

	#include <WProgram.h>

	#ifndef DEBUG_FUNC_FLOW
		#define DEBUG_FUNC_FLOW(str) \
			Serial.print(millis()); \
			Serial.print(F(": ")); \
			Serial.print(__PRETTY_FUNCTION__); \
			Serial.print(F(' ')); \
			Serial.print(__FILE__); \
			Serial.print(F(':')); \
			Serial.print(__LINE__); \
			Serial.print(F(' ')); \
			Serial.println(str);
	#endif
	
	#ifndef DEBUG_PRINT
		#define DEBUG_PRINT(str) \
			Serial.print(millis()); \
			Serial.print(F(": ")); \
			Serial.print(__PRETTY_FUNCTION__); \
			Serial.print(F(' ')); \
			Serial.print(__FILE__); \
			Serial.print(F(':')); \
			Serial.print(__LINE__); \
			Serial.print(F(' ')); \
			Serial.println(str);
	#endif

	#ifndef DEBUG_PRINT_VAL
		#define DEBUG_PRINT_VAL(val) Serial.println(val);
	#endif

#endif
 
#ifdef DEBUG

	#ifndef DEBUG_FUNC_FLOW
		#define DEBUG_FUNC_FLOW(str) Serial.println(F(str));
	#endif

	#ifndef DEBUG_PRINT
		#define DEBUG_PRINT(str) Serial.println(F(str));
	#endif

	#ifndef DEBUG_PRINT_VAL
		#define DEBUG_PRINT_VAL(val) Serial.println(val);
	#endif
			
#endif

#ifndef DEBUG_PRINT
	#define DEBUG_FUNC_FLOW(str)
	#define DEBUG_PRINT(str)
	#define DEBUG_PRINT_VAL(val)
#endif

// =========================== Done =========================== //

#endif