#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <Valve.h>

#define BUTTONPIN 4 
#define RELAYPIN 7
#define BUZZERPIN 8

#define MLPERSEC 140

extern Adafruit_SSD1306 oled;
Buzzer buzzer(BUZZERPIN);
Valve valvula;
unsigned long lastMillis;
void setup() {
	pinMode(BUTTONPIN, INPUT_PULLUP);
	pinMode(RELAYPIN, OUTPUT);
	
	Wire.begin();
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	
	lastMillis = millis();

	valvula.setConfig(EEPROM.read(0));
	Serial.begin(9600);
}
void loop() {
	static unsigned int horas = 0;
	static unsigned int msPrendido = 0;
	//oled stuff
	oledSetup(0, 30, 2);
	
	if(Serial.available() > 0){
		unsigned char newConf = Serial.read();
		valvula.setConfig(newConf);
		EEPROM.write(0, newConf);
		buzzer.ping();
		
		oled.clearDisplay();
		
		oledSetup(0, 20, 2);
		oled.print("Ajustes");
		
		oledSetup(0, 40, 2);
		oled.print("Guardados");
		
		oled.display();
		delay(200);
		
		oled.clearDisplay();
	}

	//Valve handler
	if(!digitalRead(BUTTONPIN)){	
		digitalWrite(RELAYPIN, 1);
		delay(250);
		
		valvula.addMl(MLPERSEC/4);
		valvula.run();
		msPrendido += 250;
	}
	else{
		digitalWrite(RELAYPIN, 0);
		msPrendido = 0;
	}
	
	
	//Alarma
	if(msPrendido >= valvula.getAlarma())
		buzzer.ping();
	//Horas counter
	if((millis() - lastMillis) >= HOUR){
		lastMillis = millis();
		horas++;
	}
	
	//Reset
	if(horas >= valvula.getPeriodo()){
		oledSetup(0, 20, 2);
		oled.clearDisplay();
		oled.print("NUEVO");
		oledSetup(0, 40, 2);
		oled.print("PERIODO");
		oled.display();
		
		if(valvula.getMl() < valvula.getLastMl())
			buzzer.melodia();
		else
			buzzer.ping();
		
		valvula.reset();
		delay(1000);
		valvula.run();
		horas = 0;
	}
}
