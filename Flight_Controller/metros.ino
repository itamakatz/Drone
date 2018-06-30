#ifdef ENABLE_NORMAL_PRINTS
	Metro print_metro = Metro(METRO_PRINT_INTERVAL);
#endif

#ifdef SERIAL_INPUT_ENABLE
	Metro check_serial_input_metro = Metro(METRO_CHECK_SERIAL_INTERVAL);	
#endif

Metro led_metro = Metro(METRO_LED_HIGH_INTERVAL);
Metro piezo_metro = Metro(METRO_GENERAL_INTERVAL);

bool led_state = HIGH;

void check_metros(){

	DEBUG_FUNC_FLOW("check_metros()");

// ************* led_metro ************* //

	if (led_metro.check()) {
		
		DEBUG_FUNC_FLOW("check_metros() - led_metro");
		
		if (led_state == HIGH)  { 
			led_state = LOW;
			led_metro.interval(METRO_LED_LOW_INTERVAL); // if the pin is LOW, set the interval to 0.25 seconds.
		} else {
			led_state = HIGH;
			led_metro.interval(METRO_LED_HIGH_INTERVAL); // if the pin is HIGH, set the interval to 1 second.
		}

		digitalWriteFast(LED_PIN, led_state);
	}

// ************* check_serial_input_metro ************* //

#ifdef SERIAL_INPUT_ENABLE
	// check check_serial_input_metro
	if (check_serial_input_metro.check()) {
		
		check_key();
		
		check_serial_input_metro = Metro(METRO_CHECK_SERIAL_INTERVAL);
	}
#endif

// ************* print_metro ************* //

#ifdef ENABLE_NORMAL_PRINTS
		if (print_metro.check()) {

			DEBUG_FUNC_FLOW("check_metros() - print_metro");
			
			print_serial();

			DEBUG_FUNC_FLOW("loop: after print_serial()");

			print_metro.interval(METRO_PRINT_INTERVAL);
		}
#endif
	

// ************* piezo_metro ************* //

	if (piezo_metro.check() && piezo_fifo.count() > 0) {
		if (piezo_fifo.peek() > 0){
			analogWrite(PIEZO_PIN, PIEZO_TONE);
			piezo_metro.interval(piezo_fifo.dequeue());
		} else {
			analogWrite(PIEZO_PIN, 0);
			piezo_metro.interval(-1 * piezo_fifo.dequeue());
		}
	}
}