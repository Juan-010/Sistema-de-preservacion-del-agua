
void setup() {
	Serial.begin(9600);
}

void loop() {
	unsigned char byteLeido = 0;

	if(Serial.available() > 0){
	 byteLeido = Serial.read();	
	}
	
	if(byteLeido > 100)
		tone(8, 2000, 200);
	else if(byteLeido < 100 && byteLeido != 0)
		tone(8, 1000, 200);
	else if(byteLeido == 100)
		tone(8, 1500, 200);
	delay(250);
}
