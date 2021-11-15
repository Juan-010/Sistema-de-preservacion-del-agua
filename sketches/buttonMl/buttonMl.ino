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
#define MLPERS 100
#define NORMALCONS 128000

//Time
#define HOUR 1000
#define MONINHOURS 10
#define DAYINHOURS 20

void modo(unsigned long, unsigned long, unsigned int);
void ping(int);
void oledSetup(int, int, int);
void configSetup();
void melodia(int);

unsigned long lastMillis;

// Configuracion
unsigned char config, nModo;
unsigned int timePeriod, tiempoAlarma;

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
	config = EEPROM.read(0);
	configSetup();
	//Serial
	Serial.begin(9600);
}
void loop() {
	static unsigned long mL = 0;
	static unsigned long lastMl = NORMALCONS;
	static unsigned int horas = 0;
	static unsigned int msPrendido = 0;
	//oled stuff
	oledSetup(0, 30, 2);
	
	if(Serial.available() > 0){
		config = Serial.read();
		EEPROM.write(0, config);
		configSetup();
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
		
		mL += MLPERS/4;
		modo(mL, lastMl, nModo);
		msPrendido += 250;
	}
	else{
		digitalWrite(RELAYPIN, 0);
		msPrendido = 0;
	}
	
	
	//Alarma
	if(msPrendido >= tiempoAlarma)
		ping(BUZZERPIN);

	//Horas counter
	if((millis() - lastMillis) >= HOUR){
		lastMillis = millis();
		horas++;
	}
	
	//Reset
	if(horas >= timePeriod){
		oledSetup(0, 30, 2);
		oled.clearDisplay();
		oled.print("NUEVO PERIODO");
		oled.display();
		if(mL < lastMl)
			melodia(BUZZERPIN);
		else
			ping(BUZZERPIN);
		lastMl = mL;
		mL = 0;
		
		delay(1000);
		modo(mL, lastMl, nModo);
		horas = 0;
	}
}
void modo(unsigned long mL, unsigned long lastMl, unsigned int nModo){ //Modo Normal
		if (nModo == 1) {
			oledSetup(0, 30, 2);
			oled.clearDisplay();
			oled.print(mL);
			oled.print(" ml.");
			oled.display();
		}
		
		if (nModo == 2) {
			oledSetup(0, 20, 2);
			oled.clearDisplay();
			oled.print(mL);
			oled.print(" ml./");
			
			oledSetup(0, 40, 2);
			oled.print(lastMl);
			oled.print("ml.");
			
			oled.display();
		}
		
		if (nModo == 3) {
			
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
void ping(int buzzpin){
		tone(buzzpin, 500, 200);
}
void oledSetup(int x, int y, int sz){
	oled.setTextColor(WHITE);
	oled.setCursor(x, y);
	oled.setTextSize(sz);
}

void configSetup(){
	//Modo
	if(config & (1 << 1))
		nModo = 2;
	else if(config & (1 << 2))
		nModo = 3;
	else
		nModo = 1;
	
	// Periodo
	if(config & (1 << 3))
		timePeriod = DAYINHOURS; //Diario
	else
		timePeriod = MONINHOURS; //Mensual
	
	//tiempoAlarma
	if(config & (1 << 5))
		tiempoAlarma = 5000;
	else if(config & (1 << 6))
		tiempoAlarma = 10000;
	else
		tiempoAlarma = 20000;
}
void melodia(int piezo){
	int notas[] = {523, 660, 784, 784, -1, 660, 784};
  int tempo[] = {200, 200, 200, 200,200, 200, 1000};
		for (int i = 0; i < 7; i++) {
			tone(piezo, notas[i], tempo[i]);
  		delay(tempo[i]);
	 	}
}
