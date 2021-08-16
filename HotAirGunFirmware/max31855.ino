#define filterSamples   9
uint16_t TSmoothArray[filterSamples];

void MAX31855_init(void) {
	digitalWrite(MAXCS_PIN,LOW);
	digitalWrite(MAXSCK_PIN,LOW);
	pinMode(MAXCS_PIN, INPUT); // pin to high
	pinMode(MAXSCK_PIN, OUTPUT); // pin to low 
	pinMode(MAXDO_PIN, INPUT);

}

// only positive temperatures
// timer is messed up (x8 faster), but using delay(1) here is no problem, because 1/8ms is still too much (actually delays can be as low as 100ns)
// the conversion time is about 70-100ms
int readMAX31855(void) { 
  uint16_t d = 0;

	pinMode(MAXCS_PIN, OUTPUT); // pin to low
	delayMicroseconds(100);
	pinMode(MAXSCK_PIN, OUTPUT); // pin to low 
	delayMicroseconds(100);
	// we need only 12 bytes of data. It is no sense with thermocouple to have .00 precision.
	for (byte i=0; i<12; i++) {
		pinMode(MAXSCK_PIN, OUTPUT); // pin to low 
		delayMicroseconds(100);
		d <<= 1;
		if (digitalRead(MAXDO_PIN)){d |= 1;}
		pinMode(MAXSCK_PIN, INPUT); // pin to high 
		delayMicroseconds(100);
	}
	pinMode(MAXCS_PIN, INPUT); // pin to high
	return digitalSmooth((d>1400 ? 0 : d), TSmoothArray); // higher than 1400 means negative temperature
}

// smooth algorytm for ADC reading
int digitalSmooth(uint16_t rawIn, uint16_t *sensSmoothArray){     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  uint16_t j, k, temp, top, bottom;
  unsigned long total;
  static int i;
  static uint16_t sorted[filterSamples];
  boolean done;

  i = (i + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

  for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (filterSamples - 1); j++){
      if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }

  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((filterSamples * 15)  / 100), 1); 
  top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 
  }

  return total / k;    // divide by number of samples
}

void getTemperature(){
		airTemp = readMAX31855();
	}
 
