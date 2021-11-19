#ifndef VALVE_H
#define VALVE_H
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define ANCHO 128
#define ALTO 64
#define OLED_RESET 4


#define HOUR 3600000UL
#define MONINHOURS 720
#define DAYINHOURS 24
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
#endif
