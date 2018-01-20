volatile char encoderPos = 0;	// accumulate encoder ticks in Interrupt.
volatile bool has_encoderChange = LOW;	// Indicates that Encoder has changed
unsigned long encodermillis = 0;
unsigned long encoderLongPressmillis = 0;
uint8_t value_editable=0;	// Edit Preset temperature or Fan on the fly (0 - nothing editable, 1 - Preset Temp, 2 - Fan)
unsigned long value_editable_millis;
