#include <EEPROM.h>
typedef union intToChar{
	unsigned long n;
	unsigned char c[4];
} iToC;
void setup() {
	Serial.begin(9600);
	
	iToC test; 
	test.n = 17384;
	for(int i = 0; i < 5; i++){
		EEPROM.write(i, test.c[i]);
	}	
}

void loop() {
	
}
