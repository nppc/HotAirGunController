//#define DEBUG

#define FAN_PIN     6 // Pin for controlling fan via PWM
#define LED_PIN     13
#define HEATER_PIN  9
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
#include <EEPROM.h>
#include "eeprom.h"
#include <avr/wdt.h>
	#include "oled.h"


#define PID_WINDOWSIZE 500	// upper limit of PID output
#define PID_ABSTEMPDIFFERENCE 50	// Difference in set and current temperature when PID should not work.
#define PID_P_FACTOR 1.0	//PID values are stored in EEPROM in int format. So, scale them (div) before use.
#define PID_I_FACTOR 10.0	//PID values are stored in EEPROM in int format. So, scale them (div) before use.
#define PID_D_FACTOR 1.0	//PID values are stored in EEPROM in int format. So, scale them (div) before use.

double currentTemp=0;
double setPoint=20;
double outputVal;

int pid_P, pid_I, pid_D; // PID values

unsigned long soft_pwm_millis = mmillis();
unsigned long serial_ms = mmillis();
unsigned long max31855_ms = mmillis();

uint8_t fanSpeed;
int airTemp;

int outVal = 0;

//input/output variables passed by reference, so they are updated automatically
PID myPID(&currentTemp, &outputVal, &setPoint, 0, 0, 0, DIRECT); // PID values will be set later


void setup() {
	wdt_disable();
	//Heater Off
	H_OFF;
	pinMode(HEATER_PIN, OUTPUT);
	//Duct is Off
	analogWrite(FAN_PIN,fanSpeed);

	u8g2.begin();
	u8g2.setDrawColor(2);	// Xor is default mode across all sketch.
	u8g2.setFontMode(1);	// Or is default mode
	u8g2.setFont(u8g2_font_t0_22_mf);


	initEncoder();

	// check, if button was pressed while power on (or after reset), then enter to Config mode
	if (rotaryEncRead() == 127){
		// go to config menu
		//configureParams();
	}

	//Serial.begin(115200);

	MAX31855_init();
  
	// now mess the timer (millis will be x8 faster)
	// to prevent audible noise from PWM
	// TCCR0B = TCCR0B & 0b11111000 | 0x03; //x64 - default timer speed
	TCCR0B = TCCR0B & 0b11111000 | 0x02; // x8

	#ifdef DEBUG
	analogWrite(FAN_PIN,255); //Full for testing Heater
	#endif

	fan_logo();
	mdelay(1000);
	for(uint8_t i=0;i<50;i++){readMAX31855();}	//fill smootharray

	soft_pwm_millis = mmillis()-50000;	// Before turning on the heater wait for some seconds
	
	// read PID values from EEPROM
	restore_settingsEEPROM();
	// we use FACTOR for PID values to get rid of comas in interface.
	myPID.SetTunings((float)pid_P / PID_P_FACTOR,(float)pid_I / PID_I_FACTOR,(float)pid_D / PID_D_FACTOR);
	myPID.SetOutputLimits(0, PID_WINDOWSIZE/5);	//set PID output range (1/5)

	myPID.SetMode(AUTOMATIC); // turn on PID
	
}

void loop() {
 	// reboot by holding button for 2 seconds...
	WDT_Init();	// keep system alive


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
	int val_adjust=0;	// for adjusting temperature or fan speed on the fly
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
	// adjust current temperature or fan speed
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