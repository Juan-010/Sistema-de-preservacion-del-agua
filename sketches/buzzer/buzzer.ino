/*  RickRollCode

    AUTHOR: Rowan Packard
    rowanpackard@gmail.com

    DISCLAIMER: The song "Never Gonna Give You Up" by Rick Astley
    is not the creative property of the author. This code simply
    plays a Piezo buzzer rendition of the song.
*/
#define  a3f    208     // 208 Hz
#define  b3f    233     // 233 Hz
#define  b3     247     // 247 Hz
#define  c4     261     // 261 Hz MIDDLE C
#define  c4s    277     // 277 Hz
#define  e4f    311     // 311 Hz    
#define  f4     349     // 349 Hz 
#define  a4f    415     // 415 Hz  
#define  b4f    466     // 466 Hz 
#define  b4     493     // 493 Hz 
#define  c5     523     // 523 Hz 
#define  c5s    554     // 554 Hz
#define  e5f    622     // 622 Hz  
#define  f5     698     // 698 Hz 
#define  f5s    740     // 740 Hz
#define  a5f    831     // 831 Hz 

#define rest    -1

int piezo = 8; // Connect your piezo buzzer to this pin or change it to match your circuit!
int led = LED_BUILTIN; 
int notas[] = {523, 660, 784, 784, -1, 660, 784};
int tempo[] = {200, 200, 200, 200,200, 200, 1000};

void setup()
{
  pinMode(piezo, OUTPUT);
	Serial.begin(9600);
}
void loop()
{
	static int i = 0;
	Serial.println(i);
	tone(piezo, notas[i], tempo[i]);
	delay(tempo[i]);
	if(i == 6)
		i = 0;
	else
		i++;

}

