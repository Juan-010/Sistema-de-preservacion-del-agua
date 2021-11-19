#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

//OLED
#define ANCHO 128
#define ALTO 64
#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);


//Time
#define HOUR 1000
#define MONINHOURS 15
#define DAYINHOURS 10


	
void ping(int);
void oledSetup(int, int, int);
void melodia(int);

unsigned long lastMillis;

//Valve
#define BUTTONPIN 4 
#define RELAYPIN 7
#define BUZZERPIN 8
#define MLPERS 100
#define NORMALCONS 128000
class Valve{
	public:
		Valve(){
			config = 0x29; // 0010 1001 (29)
			mL = 0;
			lastMl = NORMALCONS;
		}
		unsigned long getMl(){ return mL; }
		unsigned long getLastMl() { return lastMl; }
		unsigned char getModo(){
			if(config & (1 << 1))
				return 2;
			else if(config & (1 << 2))
				return 3;
			else
				return 1;
		}
		unsigned int getAlarma(){
			if(config & (1 << 5))
				return 5000;
			else if(config & (1 << 6))
				return 10000;
			else
				return 20000;
		}
		unsigned int getPeriodo(){
			if(config & (1 << 3))
				return DAYINHOURS; //Diario
			else
				return MONINHOURS; //Mensual
		}

		void setConfig(unsigned char newConfig){
			config = newConfig;
		}
		void reset(){
			lastMl = mL;
			mL = 0;
		}
		void addMl(unsigned int addedMl){
			mL += addedMl;
		}

		void run(){
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
		
	private:
		unsigned char config;
		unsigned long mL;
		unsigned long lastMl;
};
Valve valvula;
// Configuracion

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
		ping(BUZZERPIN);
		
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
		ping(BUZZERPIN);

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
			melodia(BUZZERPIN);
		else
			ping(BUZZERPIN);
		valvula.reset();
		delay(1000);
		valvula.run();
		horas = 0;
	}
}
void ping(int buzzpin){
		tone(buzzpin, 500, 200);
}
void oledSetup(int x, int y, int sz){
	oled.setTextColor(WHITE);
	oled.setCursor(x, y);
	oled.setTextSize(sz);
}
void melodia(int piezo){
	int notas[] = {523, 660, 784, 784, -1, 660, 784};
  int tempo[] = {200, 200, 200, 200,200, 200, 1000};
		for (int i = 0; i < 7; i++) {
			tone(piezo, notas[i], tempo[i]);
  		delay(tempo[i]);
	 	}
}
