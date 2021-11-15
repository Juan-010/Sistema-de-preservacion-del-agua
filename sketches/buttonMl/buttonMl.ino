#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
//OLED
#define ANCHO 128
#define ALTO 64

#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

//Valve
#define BUTTONPIN 4 
#define RELAYPIN 7
#define BUZZERPIN 8
#define MLPERS 100 //Config

//Time
#define HOUR 3600000
#define MONINHOURS 720
#define DAYINHOURS 24

#define ALARMATIEMPO 5000 //Config
void modo1(unsigned long);
void ping(int);
void oledSetup(int, int, int);

long lastMillis;
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

	//Serial
	Serial.begin(9600);
}
unsigned long long period = DAYINHOURS;
void loop() {
	static unsigned long mL = 0;
	static unsigned int horas = 0;
	static unsigned int msPrendido = 0;
	//oled stuff
	oledSetup(0, 30, 2);
	//Valve handler
	if(!digitalRead(BUTTONPIN)){	
		
		digitalWrite(RELAYPIN, 1);
		delay(250);
		
		mL += MLPERS/4;
		modo1(mL);
		msPrendido += 250;

	}

	else{
		digitalWrite(RELAYPIN, 0);
		msPrendido = 0;
	}
	
	//Horas counter
	if((millis() - lastMillis) >= HOUR){
		lastMillis = millis();
		horas++;
	}
	
	//Alarma
	if(msPrendido >= ALARMATIEMPO){
		ping(BUZZERPIN);
	}

	
	//Reset
	if(horas >= period){
		//lastMl = mL;
		mL = 0;
		
		ping(BUZZERPIN);
		oledSetup(0, 30, 2);
		oled.clearDisplay();
		oled.print("NUEVO PERIODO");
		oled.display();
		delay(1000);
		
		oledSetup(0, 30, 2);
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();

		horas = 0;
	}
}
void modo1(unsigned long mL){ //Modo Normal
		oledSetup(0, 30, 2);
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();
}
void ping(int buzzpin){
		tone(buzzpin, 500, 200);
}
void oledSetup(int x, int y, int sz){
	oled.setTextColor(WHITE);
	oled.setCursor(x, y);
	oled.setTextSize(sz);
}
