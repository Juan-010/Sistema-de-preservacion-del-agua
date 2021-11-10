#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//OLED
#define ANCHO 128
#define ALTO 64

#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

//Valve
#define BUTTONPIN 4 
#define RELAYPIN 7
#define BUZZERPIN 8
#define MLPERS 100
#define HOUR 3600000

long lastMillis;
void setup() {
	pinMode(BUTTONPIN, INPUT_PULLUP);
	pinMode(RELAYPIN, OUTPUT);
	pinMode(BUZZERPIN, OUTPUT);
	Wire.begin();
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	lastMillis = millis();
}

void loop() {
	static unsigned long mL = 0;
	static unsigned int horas = 0;
	
	//oled stuff
	oled.setTextColor(WHITE);
	oled.setCursor(0, 30);
	oled.setTextSize(2);
	

	if(!digitalRead(BUTTONPIN)){	
		digitalWrite(RELAYPIN, 1);
		delay(250);
		mL += MLPERS/4;
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();
	}

	else
		digitalWrite(RELAYPIN, 0);
	
	
	// Reset Handler
	if((millis() - lastMillis) >= HOUR){
		lastMillis = millis();
		horas++;
	}

	if(horas >= 24){
		//lastMl = mL;
		mL = 0;
		
		tone(8, 500, 200);
		oled.clearDisplay();
		oled.print("NUEVO DIA");
		oled.display();
		delay(200);
		
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();

		horas = 0;
	}
}
