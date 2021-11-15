#include <EEPROM.h>
typedef union intToChar{
	unsigned long n;
	unsigned char c[4];
} iToC;
void setup() {
	Serial.begin(9600);
	
	iToC test; 
	for(int i = 0; i < 5; i++){
		test.c[i] = EEPROM.read(i);
	}	
	Serial.println(test.n);
}

void loop() {
	
}
