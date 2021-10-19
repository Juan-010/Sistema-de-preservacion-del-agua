#define RELAYPIN 7
#define BUTTONPIN 8
void setup() {
	pinMode(RELAYPIN, OUTPUT);
	pinMode(BUTTONPIN, INPUT_PULLUP);
}
void loop() {
	digitalWrite(RELAYPIN,!digitalRead(BUTTONPIN));
}
