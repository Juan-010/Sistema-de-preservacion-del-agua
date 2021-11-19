#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//OLED
#define ANCHO 128
#define ALTO 64
#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);
//Time
#define HOUR 1000
#define MONINHOURS 15
#define DAYINHOURS 10

#ifndef BUZZERPIN
#define BUZZERPIN 8
#endif

#define NORMALCONS 128000
	
void oledSetup(int, int, int);
class Buzzer{
	public:
		Buzzer(int = BUZZERPIN);
		void ping();
		void melodia();
	private:
		int pin; 
};


Buzzer::Buzzer(int buzzpin){
	pin = buzzpin;
}
void Buzzer::ping(){
	tone(pin, 500, 200);
}
void Buzzer::melodia(){
	int notas[] = {523, 660, 784, 784, -1, 660, 784};
	int tempo[] = {200, 200, 200, 200,200, 200, 1000};
		for (int i = 0; i < 7; i++) {
			tone(pin, notas[i], tempo[i]);
			delay(tempo[i]);
 		}

}










//Valve
class Valve{
	public:
		Valve();
		unsigned long getMl(){ return mL; }
		unsigned long getLastMl() { return lastMl; }
		unsigned char getModo();
		unsigned int getAlarma();
		unsigned int getPeriodo();
		void setConfig(unsigned char);
		void reset();
		void addMl(unsigned int addedMl);
		void run();
	private:
		unsigned char config;
		unsigned long mL;
		unsigned long lastMl;
};
Valve::Valve(){
	config = 0x29; // 0010 1001 (29)
	mL = 0;
	lastMl = NORMALCONS;
}

unsigned char Valve::getModo(){
	if(config & (1 << 1))
		return 2;
	else if(config & (1 << 2))
		return 3;
	else
		return 1;
}

unsigned long Valve::getAlarma(){
	if(config & (1 << 5))
		return 5000;
	else if(config & (1 << 6))
		return 10000;
	else
		return 20000;
}

void Valve::getPeriodo(){
	if(config & (1 << 3))
		return DAYINHOURS; //Diario
	else
		return MONINHOURS; //Mensual
}

void Valve::setConfig(unsigned char newConfig){
	config = newConfig;
}

void Valve::reset(){
	lastMl = mL;
	mL = 0;
}
void Valve::addMl(unsigned int addedMl){
	mL += addedMl;

}
void Valve::run(){
	if (getModo() == 1) {
		oledSetup(0, 30, 2);
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml.");
		oled.display();
	}

	if (getModo() == 2) {
		oledSetup(0, 20, 2);
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml./");
		
		oledSetup(0, 40, 2);
		oled.print(lastMl);
		oled.print("ml.");
		
		oled.display();
	}
	
	if (getModo() == 3) {
		
		oledSetup(0, 20, 2);
		oled.clearDisplay();
		oled.print(mL);
		oled.print(" ml./");
		
		oledSetup(0, 40, 2);
		oled.print(NORMALCONS);
		oled.print("ml.");
		
		oled.display();
	}
}
void oledSetup(int x, int y, int sz){
	oled.setTextColor(WHITE);
	oled.setCursor(x, y);
	oled.setTextSize(sz);
}
