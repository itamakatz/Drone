#define PIEZZO_SHORT_DELAY 200
#define PIEZZO_VERY_LONG_DELAY 1000

void piezo_notification(Piezo_modes mode){
	
	if (last_mode != mode) {
		switch (mode) {
			case Piezo_modes::on:
				piezo_fifo.flush();
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_VERY_LONG_DELAY);
				piezo_fifo.enqueue(-1);
				break;
			case Piezo_modes::off:
				piezo_fifo.flush();
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1);
				break;
			case Piezo_modes::set_target_angles:
				piezo_fifo.flush();
				piezo_fifo.enqueue(PIEZZO_VERY_LONG_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_VERY_LONG_DELAY);
				piezo_fifo.enqueue(-1);
			case Piezo_modes::set_sensitivity:
				piezo_fifo.flush();
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(PIEZZO_SHORT_DELAY);
				piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);				
				piezo_fifo.enqueue(-1);
			default:
				break;
		}
	}

	last_mode = mode;

	// analogWrite(PIEZO_PIN, 0);
}