#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//OLED
#define ANCHO 128
#define ALTO 64

#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

//Valve
#define BUTTONPIN 3 
#define MLPERS 50
long lastMillis;
void setup() {
	pinMode(BUTTONPIN, INPUT_PULLUP);
	pinMode(13, OUTPUT);
	pinMode(8, OUTPUT);
	Wire.begin();
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	lastMillis = millis();
}

void loop() {
	static unsigned long mL = 0;
	//oled stuff
	oled.setTextColor(WHITE);
	oled.setCursor(0, 30);
	oled.setTextSize(2);
	if(!digitalRead(BUTTONPIN)){
		digitalWrite(13, 1);
		delay(250);
		mL += MLPERS;
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();
	}
	else
		digitalWrite(13,0);
	if((millis() - lastMillis) >= 30000){
		lastMillis = millis();
		tone(8, 500, 200);
		mL = 0;
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();
	}
}
