#include "leds.h"

extern volatile bool started;
const int led[] = {A2, A3, A4, A5};
int edellinenLed = -1;

void initializeLeds() {
// Asettaa analogia I/O:n output tilaan ja alustaa pinnit
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++) {
  pinMode(led[i],OUTPUT);
}
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++) {
  digitalWrite(led[i], LOW);
  }
}


void setLed(byte ledNumber) 
{
    if(edellinenLed==ledNumber)
    {
    digitalWrite(led[edellinenLed], LOW);
    delay(100);
    digitalWrite(led[ledNumber], HIGH);
    }
    else{
      clearAllLeds();
      digitalWrite(led[ledNumber], HIGH);
    }
    edellinenLed = ledNumber;
}

void clearAllLeds() {
// Sammuttaa kaikki ledit
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++) {
  digitalWrite(led[i], LOW);
  }
}

void setAllLeds() {
// Sytyttää kaikki ledit
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++) {
  digitalWrite(led[i], HIGH);
  }  
}

void show1() {
//Laskee binääreissä 0-15 käyttäen ledejä
byte count=0;
while(count<16) {
  if(started == true){
    clearAllLeds();
    return;
  }
  for(int i=0; i< sizeof(led) / sizeof(led[0]); i++) {
digitalWrite(led[i],bitRead(count,i));
}
  count++;
  delay(500);
  }
}
void show2(int rounds) {
//Kierrättää valot kaikki päällä vuoronperään 
int aika=1500;
for(int y=0;y<=rounds;y++) {
  for(int i=0; i< sizeof(led) / sizeof(led[0]); i++) {
      digitalWrite(led[i],HIGH);
      delay(aika);
      digitalWrite(led[i],LOW);
    }
    aika=aika-250;
}
if(aika<250) {
  aika=250;
}
}
