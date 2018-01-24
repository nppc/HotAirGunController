//#define DEBUG

#define FAN_PIN     6 // Pin for controlling fan via PWM
#define LED_PIN     13
#define HEATER_PIN  11
#define MAXSCK_PIN  2
#define MAXCS_PIN   5
#define MAXDO_PIN   7

#define encoderPinA   3	// Interrupt pin (coupled with capacitor to GND)
#define encoderPinB   4 // Interrupt pin (coupled with capacitor to GND)
#define BUTTON_PIN   12 // Pin for knob button

#define TIMER_MULTIPLIER  8 // if timer has normal (x64) prescaller, then 1

// some macros
#define mdelay(val) delay(val * TIMER_MULTIPLIER)
#define mmillis() (millis() / TIMER_MULTIPLIER)
#define H_ON   digitalWrite(HEATER_PIN,HIGH);digitalWrite(LED_PIN, HIGH);
#define H_OFF   digitalWrite(HEATER_PIN,LOW);digitalWrite(LED_PIN, LOW);

#include <PID_v1.h>
#include <U8g2lib.h>
#include "encoder.h"

#define PID_WINDOWSIZE 500	// upper limit of PID output
#define PID_ABSTEMPDIFFERENCE 50	// Difference in set and current temperature when PID should not work.
#define PID_P_FACTOR 1.0	//PID values are stored in EEPROM in int format. So, scale them (div) before use.
#define PID_I_FACTOR 10.0	//PID values are stored in EEPROM in int format. So, scale them (div) before use.
#define PID_D_FACTOR 1.0	//PID values are stored in EEPROM in int format. So, scale them (div) before use.

double currentTemp=0;
double setPoint=20;
double outputVal;

int pid_P = 50, pid_I = 3, pid_D = 100; // PID values

//input/output variables passed by reference, so they are updated automatically
PID myPID(&currentTemp, &outputVal, &setPoint, 0, 0, 0, DIRECT); // PID values will be set later

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

unsigned long soft_pwm_millis = mmillis();
unsigned long serial_ms = mmillis();
unsigned long max31855_ms = mmillis();

uint8_t fanSpeed=0;
int airTemp;

int outVal = 0;



void setup() {
	//Heater Off
	H_OFF;
	pinMode(HEATER_PIN, OUTPUT);
	//Duct is Off
	analogWrite(FAN_PIN,0);
	
	myPID.SetTunings((float)pid_P / PID_P_FACTOR,(float)pid_I / PID_I_FACTOR,(float)pid_D / PID_D_FACTOR);
	myPID.SetOutputLimits(0, PID_WINDOWSIZE/5);	//set PID output range (1/5)

	initEncoder();
		
	waitUntilButtonReleased(); // in case it was
	
	//Serial.begin(115200);

	MAX31855_init();
  
	u8g2.begin();
	u8g2.setDrawColor(2);	// Xor is default mode across all sketch.
	u8g2.setFontMode(1);	// Or is default mode

	// now mess the timer (millis will be x8 faster)
	// to prevent audible noise from PWM
	// TCCR0B = TCCR0B & 0b11111000 | 0x03; //x64 - default timer speed
	TCCR0B = TCCR0B & 0b11111000 | 0x02; // x8

	fan_logo();
	mdelay(1000);
	for(uint8_t i=0;i<50;i++){readMAX31855();}	//fill smootharray

	myPID.SetMode(AUTOMATIC); // turn on PID

	soft_pwm_millis = mmillis()-50000;	// Before turning on the heater wait for some seconds
	
}

void loop() {
 	

	if(max31855_ms+80 < mmillis()) {
		max31855_ms = mmillis();
		airTemp = readMAX31855();
		currentTemp = airTemp;	// variable for PID
	}	
	adjustValues();
	u8g2.clearBuffer();
	showMainData();
	u8g2.sendBuffer();

	analogWrite(FAN_PIN,map(fanSpeed,0,100,0,255));

	
	// use PID only when difference is small (to prevent windup of I)
	if(abs(setPoint-currentTemp)<PID_ABSTEMPDIFFERENCE){
		myPID.Compute();
	}else{
		outputVal = (setPoint > currentTemp ? PID_WINDOWSIZE : 0); // ON/OFF control
	}
	
	if(outputVal>0 && setPoint>20){doSoftwarePWM((uint16_t)outputVal);}else{H_OFF;}

}


// PWM output 
void doSoftwarePWM(uint16_t pwm_val){
  if (mmillis() - soft_pwm_millis > (PID_WINDOWSIZE))
    { //time to shift the Relay Window
    soft_pwm_millis += PID_WINDOWSIZE;
    }
  if (pwm_val < mmillis() - soft_pwm_millis){H_OFF}else{H_ON}
}


void adjustValues() {
	int val_adjust=0;	// for adjusting temperature or time on the fly
	char encVal = 127;  // signed value - just enter to the loop
	while (encVal == 127) { //loop here while button is pressed (waiting longer than 2 seconds will reset the board (Exit to the init menu).
		encVal = rotaryEncRead();
		if(encVal!=127) {
			val_adjust = encVal;
		}else if(encVal==127){
			H_OFF;	// turn off heater, because we will freeze here for some time...
			waitUntilButtonReleased();
			value_editable++;	// change edit mode
			if(value_editable>1){value_editable=0;}
			value_editable_millis=mmillis();		// start timer for edit time within 3 seconds
		}
	}
	// adjust current temperature or timer
	if(val_adjust!=0){
		val_adjust*=10; // adjust in 10's steps
		if(value_editable==1){
			fanSpeed=constrain(fanSpeed+val_adjust,30,100);
		}else {
			setPoint=constrain((int)setPoint+val_adjust,20,500);
		}
		value_editable_millis=mmillis();
	}
	// reset timer_editable flag if edit time expired
	if(value_editable>0 && value_editable_millis+3000<mmillis()) {value_editable=0;}
}	