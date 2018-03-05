// Encoder routines. Uses one Interrupt.

void initEncoder() {    
	pinMode(encoderPinA, INPUT_PULLUP); 
    pinMode(encoderPinB, INPUT_PULLUP); 
    pinMode(BUTTON_PIN, INPUT_PULLUP); 
    attachInterrupt(1, INT_doEncoder, FALLING);  // encoder pin on interrupt 1 - pin 3
}

char rotaryEncRead() {
  noInterrupts();
  char tmp = encoderPos;
  encoderPos=0;  // reset encoder
  interrupts();
  if(!digitalRead(BUTTON_PIN)){tmp=127;} // read button
  return tmp;
}

void INT_doEncoder() {
    // If interrupts come faster than 5ms, assume it's a bounce and ignore
    if (mmillis() - encodermillis > 5) {
        if (!digitalRead(encoderPinB))
            encoderPos++;
        else
            encoderPos--;

		has_encoderChange = HIGH;
        }
    encodermillis = mmillis();
}

// determine if rotary encoder was pressed longer than 2 seconds
/*
bool is_rotaryEncLongPress() {
	 if(digitalRead(BUTTON_PIN)){
		 // button is not pressed
		 encoderLongPressmillis=mmillis();
	 }else{
		 // button is pressed
		 // how long?
		 if((encoderLongPressmillis+2000)<mmillis()){
			 // Long press engaged
			 return true;
			 encoderLongPressmillis=mmillis();	// reset counter
		 }
	 }
	 return false;
}
*/
void waitUntilButtonReleased(){
	// wait until button is depressed
#ifdef SUSPEND_LONGPRESS
	int delaycounter=0;
	while(rotaryEncRead() == 127){
		if(SafeTemp < airTemp || suspendMode){
			WDT_Init();
			mdelay(50);
			delaycounter++;
			if(delaycounter>30){
				// enable/disable cooldown mode
				if(!suspendMode){
					suspendMode=1;
					printSuspend();
				}else{
					suspendMode=0;
					printResume();
				}
				while(rotaryEncRead() == 127){WDT_Init();}
			}
			
		}
	} // keep system alive
#else
	while(rotaryEncRead() == 127){
		if(SafeTemp < airTemp){
			WDT_Init();
		}
	}
#endif
mdelay(50); // wait for noise is gone from button contacts
}