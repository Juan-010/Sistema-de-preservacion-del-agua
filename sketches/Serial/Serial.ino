
void setup() {
	Serial.begin(9600);
	pinMode(13, OUTPUT);
}

void loop() {
	if(Serial.available() > 0){
		char car = Serial.read();
		if(car == 'Y')
			digitalWrite(13, HIGH);
		else if(car == 'N')
			digitalWrite(13, LOW);
	}
}
