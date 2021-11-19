#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <Valve.h>

extern Adafruit_SSD1306 oled;
Buzzer buzzer;
Valve valvula;
unsigned long lastMillis;

#define BUTTONPIN 4 
#define RELAYPIN 7
#define MLPERS 100

void setup() {
	pinMode(BUTTONPIN, INPUT_PULLUP);
	pinMode(RELAYPIN, OUTPUT);
	pinMode(BUZZERPIN, OUTPUT);
	
	//I2C
	Wire.begin();
	
	//OLED
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	
	//Ms tracker
	lastMillis = millis();

	//Config
	valvula.setConfig(EEPROM.read(0));
	//Serial
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
		
		valvula.addMl(MLPERS/4);
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
		oledSetup(0, 30, 2);
		oled.clearDisplay();
		oled.print("NUEVO PERIODO");
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
