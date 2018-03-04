// Control the fan according to the temperature
// If Preset temperature is higher than 20, then run fan on preset speed.
// If heater is off (Preset temperature is less than 30), then control fan automatically, until it cools down to 50 deg.
void fanControl(){
	if(setPoint>20){
		// heater is working
		fanSpeed_actual=fanSpeed;
	}else if (airTemp>100){
		fanSpeed_actual=100;
	}else { 
		if((fanSpeed_millis+2000) < mmillis()){
			fanSpeed_millis = mmillis();
			if (airTemp>80){
				fanSpeed_actual-=5;if(fanSpeed_actual<80){fanSpeed_actual=80;}
			}else if (airTemp>50){
				fanSpeed_actual-=5;if(fanSpeed_actual<60){fanSpeed_actual=60;}
			}else if(airTemp<45 && fanSpeed_actual!=0){
				fanSpeed_actual-=5;if(fanSpeed_actual<30){fanSpeed_actual=0;}
			}
		}
	}
	analogWrite(FAN_PIN,map(fanSpeed_actual,0,100,0,255));
}