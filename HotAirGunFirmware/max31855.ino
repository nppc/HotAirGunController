void MAX31855_init(void) {
  pinMode(MAXCS_PIN, OUTPUT);
  digitalWrite(MAXCS_PIN, HIGH);
  pinMode(MAXSCK_PIN, OUTPUT); 
  pinMode(MAXDO_PIN, INPUT);
}

// only positive temperatures
// timer is messed up (x8 faster), but using delay(1) here is no problem, because 1/8ms is still too much (actually delays can be as low as 100ns)
uint16_t readMAX31855(void) { 
  uint16_t d = 0;

  digitalWrite(MAXCS_PIN, LOW);
  delay(1);
  digitalWrite(MAXSCK_PIN, LOW);
  delay(1);
  // we need only 12 bytes of data. It is no sense with thermocouple to have .00 precision.
  for (byte i=0; i<12; i++) {
    digitalWrite(MAXSCK_PIN, LOW);
    delay(1);
    d <<= 1;
    if (digitalRead(MAXDO_PIN)){d |= 1;}
    digitalWrite(MAXSCK_PIN, HIGH);
    delay(1);
  }
  digitalWrite(MAXCS_PIN, HIGH);
  return (d>1400 ? 0 : d); // higher than 1400 means negative temperature
}
