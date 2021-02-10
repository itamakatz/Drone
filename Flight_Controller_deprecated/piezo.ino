void piezo_notification(Piezo_modes mode){
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
		case Piezo_modes::piezo_set_target_angles:
			piezo_fifo.flush();
			piezo_fifo.enqueue(PIEZZO_VERY_LONG_DELAY);
			piezo_fifo.enqueue(-1 * PIEZZO_SHORT_DELAY);
			piezo_fifo.enqueue(PIEZZO_VERY_LONG_DELAY);
			piezo_fifo.enqueue(-1);
		default:
			break;
	}
}