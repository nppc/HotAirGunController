#define MENU_ITEMS	5+1 // 5 parameters plus 1 Save/Exit

void configureParams(){
	uint8_t item = 1;
	boolean edit = false;
	
	printEnterSettings();
	waitUntilButtonReleased();	
	printConfParam(item, edit); 
	
	// wait for encoder
	char encVal = 0;  // signed value - nothing is pressed
	while (1) {
		encVal = rotaryEncRead();
		if(encVal!=0 && encVal!=127) {
			if(!edit){
				item=constrain(item + encVal,1, MENU_ITEMS);
			} else {
				// adjust selected value
				switch (item) {
					case 1:
						pid_P = constrain(pid_P+encVal*10,0,990);
						break;
					case 2:
						pid_I = constrain(pid_I+encVal,0,100);
						break;
					case 3:
						pid_D = constrain(pid_D+encVal*10,0,990);
						break;
					case 4:	// Fan speed
						fanSpeed = constrain(fanSpeed+encVal*10,30,100);
						break;
					case 5:	// Safe Temperature for entering Config
						SafeTemp = constrain(SafeTemp+encVal*10,40,500);
						break;
				} 
			}
		}
		if(encVal==127){ // button is pressed
			if(item==MENU_ITEMS){
				printSavingSettings();
				store_settingsEEPROM();
				while(1){}	// reboot the board
			}
			// switch edit mode
			edit=!edit;
			waitUntilButtonReleased();
		}
		WDT_Init();
		printConfParam(item, edit);
		getTemperature();	// updates airTemp variable
		fanControl();
		
	}
}

void printEnterSettings(){
	u8g2.clearBuffer();
	u8g2.setCursor(0, 24);
	u8g2.print(F("CONFIG"));
	u8g2.sendBuffer();
}

void printSavingSettings(){
	u8g2.clearBuffer();
	u8g2.setCursor(0, 24);
	u8g2.print(F("Saving..."));
	u8g2.sendBuffer();
}

// item - number of configurable item
// edit - if TRUE, then highlight the edited value
void printConfParam(uint8_t item, boolean edit){
	u8g2.clearBuffer();
	u8g2.setDrawColor(2);	//inverse mode
	if(edit && item != MENU_ITEMS){
		u8g2.drawBox(95,6,128-95,32-5*2);
	}
	u8g2.setCursor(0, 24);
	switch (item) {
		case 1:
			u8g2.print(F("PID P"));
			break;
		case 2:
			u8g2.print(F("PID I"));
			break;
		case 3:
			u8g2.print(F("PID D"));
			break;
		case 4:	// Preheat temperature
			u8g2.print(F("Fan %"));
			break;
		case 5:	// Safe temperature
			u8g2.print(F("Safe T"));
			break;
		default: // Save settings and exit (last menu item)
			u8g2.print(F("Save & Exit"));
			break;
	} 
	if(item!=MENU_ITEMS){
		u8g2.setCursor(95, 24);
		u8g2.print(getValueForConfigItem(item));
	}
	u8g2.sendBuffer();
}

uint16_t getValueForConfigItem(uint8_t item) {
	switch (item) {
		case 1:
			return pid_P;
			break;
		case 2:
			return pid_I;
			break;
		case 3:
			return pid_D;
			break;
		case 4:
			return fanSpeed;
			break;
		case 5:	// Safe temperature
			return SafeTemp;
			break;
	} 
}