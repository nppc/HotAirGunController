// Control the fan according to the temperature
// If Preset temperature is higher than 20, then run fan on preset speed.
// If heater is off (Preset temperature is less than 30), then control fan automatically, until it cools down to 50 deg.
void fanControl(){
	if(setPoint>20){
		// heater is working
		fanSpeed_actual=fanSpeed;
	}else{
		if (airTemp>50){
			fanSpeed_actual=60;
		}	else if(airTemp<45){
				if((fanSpeed_millis+2000) < mmillis()){
					fanSpeed_millis = mmillis();
					fanSpeed_actual = (fanSpeed_actual<=30 ? 0 : fanSpeed_actual-5);
				}
		}
	}
	analogWrite(FAN_PIN,map(fanSpeed_actual,0,100,0,255));
}