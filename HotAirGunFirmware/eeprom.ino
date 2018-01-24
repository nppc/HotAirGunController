void restore_settingsEEPROM(){
	pid_P = constrain(readEEPROMint(EEPROM_PID_P),0,990);
	pid_I = constrain(readEEPROMint(EEPROM_PID_I),0,100);
	pid_D = constrain(readEEPROMint(EEPROM_PID_D),0,990);
	fanSpeed = constrain(readEEPROMint(EEPROM_FAN_SPEED),30,100);
}

void store_settingsEEPROM(){
	writeEEPROMint(EEPROM_PID_P,pid_P);
	writeEEPROMint(EEPROM_PID_I,pid_I);
	writeEEPROMint(EEPROM_PID_D,pid_D);
	writeEEPROMint(EEPROM_FAN_SPEED,fanSpeed);
}

uint16_t readEEPROMint(uint8_t addr){
	return EEPROM.read(addr)+EEPROM.read(addr+1)*256;
}

void writeEEPROMint(uint8_t addr, uint16_t value){
	EEPROM.update(addr, lowByte(value));
	EEPROM.update(addr+1, highByte(value));
}

