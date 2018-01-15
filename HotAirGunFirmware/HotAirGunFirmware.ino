#define DEBUG

#define FAN_PIN     6 // Pin for controlling fan via PWM
#define LED_PIN     13
#define HEATER_PIN  12
#define MAXSCK_PIN  2
#define MAXCS_PIN   3
#define MAXDO_PIN   4

#define TIMER_MULTIPLIER  8 // if timer has normal (x64) prescaller, then 1

#define PID_WINDOWSIZE  500 // software PWM period for Heater

// some macros
#define mdelay(val) delay(val * TIMER_MULTIPLIER)
#define mmillis() (millis() / TIMER_MULTIPLIER)
#define H_ON   digitalWrite(HEATER_PIN,HIGH);digitalWrite(LED_PIN, HIGH);
#define H_OFF   digitalWrite(HEATER_PIN,LOW);digitalWrite(LED_PIN, LOW);


unsigned long soft_pwm_millis = mmillis();
unsigned long serial_ms = mmillis();

int outVal = 0;


void setup() {
  //Heater Off
  H_OFF;
  pinMode(HEATER_PIN, OUTPUT);
  //Duct is Off
  analogWrite(FAN_PIN,0);
  
  Serial.begin(115200);

  MAX31855_init();
  
  // now mess the timer (millis will be x8 faster)
  // to prevent audible noise from PWM
  // TCCR0B = TCCR0B & 0b11111000 | 0x03; //x64 - default timer speed
  TCCR0B = TCCR0B & 0b11111000 | 0x02; // x8
  
  #ifdef DEBUG
  analogWrite(FAN_PIN,255); //Full for testing Heater
  #endif
}

void loop() {
  
	#ifdef DEBUG
	if (serial_ms+1000 < mmillis()) {
		serial_ms = mmillis();
		Serial.print(F("Temp = "));
		Serial.println(readMAX31855());
	}	
	#endif

    if (Serial.available() > 0) {
		char incomingByte = Serial.read();
		incomingByte=constrain(incomingByte,48,57);
		outVal=map(incomingByte,48,57,0,100);
		Serial.print(F(": I = "));
		Serial.print(incomingByte);
		Serial.print(F(", O = "));
		Serial.println(outVal);
    }
	if(outVal>0){doSoftwarePWM((uint16_t)outVal);}else{H_OFF;}

}


// PWM output 
void doSoftwarePWM(uint16_t pwm_val){
  if (mmillis() - soft_pwm_millis > (PID_WINDOWSIZE))
    { //time to shift the Relay Window
    soft_pwm_millis += PID_WINDOWSIZE;
    }
  if (pwm_val < mmillis() - soft_pwm_millis){H_OFF}else{H_ON}
}

