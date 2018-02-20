#include "Arduino.h"
#include <avr/wdt.h>


bool intentionalReset=0;

//The setup function is called once at startup of the sketch
void setup()
{
	wdt_enable(WDTO_2S);

	Serial.begin(115200);
	Serial.println(F("WDT test suite!"));
	Serial.println(F("press \'*\' to loop"));
	delay(100);

}

// The loop function is called in an endless loop
void loop()
{
	static int i=0;


	if(!intentionalReset)
		wdt_reset();
	else{
		Serial.println("\nresetting");
		while(1);
	}

	if(++i<20)
		Serial.print(F(". "));
	else{
		i=0;
		Serial.println();
	}
	delay(100);

}


void serialEvent(){
  while(Serial.available()){
    char inChar = (char) Serial.read();
    if(inChar=='*'){
      intentionalReset = true;
    }
  }
}
