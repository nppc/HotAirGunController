#include "Adafruit_MAX31855.h"

#define FAN_PIN     6 // Pin for controlling fan via PWM
#define LED_PIN     13
#define HEATER_PIN  12
#define MAXSCK_PIN  2
#define MAXCS_PIN   3
#define MAXDO_PIN   4

#define PID_WINDOWSIZE  500 * 8
unsigned long soft_pwm_millis=millis();

#define H_ON   digitalWrite(HEATER_PIN,HIGH);digitalWrite(LED_PIN, HIGH);
#define H_OFF   digitalWrite(HEATER_PIN,LOW);digitalWrite(LED_PIN, LOW);


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
  
  analogWrite(FAN_PIN,255); //Full for testing Heater
}

void loop() {
  
  Serial.print("Int. Temp = ");
  Serial.println(readMAX31855());
  delay(1000 * 8);

    if (Serial.available() > 0) {
      char incomingByte = Serial.read();
      incomingByte=constrain(incomingByte,48,57);
      int outVal=map(incomingByte,48,57,0,100);
      doSoftwarePWM((uint16_t)outVal); 
      Serial.print(": I = ");
      Serial.print(incomingByte);
      Serial.print(", O = ");
      Serial.println(outVal);
    }
}


// PWM output 
void doSoftwarePWM(uint16_t pwm_val){
  if (millis() - soft_pwm_millis > (PID_WINDOWSIZE))
    { //time to shift the Relay Window
    soft_pwm_millis += PID_WINDOWSIZE;
    }
  if (pwm_val < millis() - soft_pwm_millis){H_OFF}else{H_ON}
}

