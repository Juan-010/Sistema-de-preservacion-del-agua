#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO 128
#define ALTO 64

#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);
void setup() {
	Wire.begin();
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	Serial.begin(9600);
}

void loop() {
		oled.clearDisplay();
		oled.setTextColor(WHITE);
		oled.setCursor(0,0);
		oled.setTextSize(1);
		oled.setCursor(10, 30);
		oled.setTextSize(2);
	if(Serial.available() > 0){
		unsigned char test = Serial.read();
		for(int i = 7; i >= 0 ; i--)
			oled.print(test & (1 << i) ? 1 : 0);
		oled.display();
}
}
