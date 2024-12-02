#include "leds.h"

const int led[] = {A2, A3, A4, A5};
int edellinenLed = -1;
int aikavali = 1000;

void initializeLeds()
{
// Asettaa analogia I/O:n output tilaan ja alustaa pinnit
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++){
  pinMode(led[i],OUTPUT);
}
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++){
  digitalWrite(led[i], LOW);
}
}


void setLed(byte ledNumber)
{
    // see requirements for this function from leds.h
    unsigned long aika = millis();
    if(edellinenLed==ledNumber){
        digitalWrite(led[edellinenLed], LOW);
        while(millis() < aika + aikavali){}
    }
    digitalWrite(led[edellinenLed], LOW);
    digitalWrite(led[ledNumber], HIGH);
    edellinenLed = ledNumber;
}
clearAllLeds()
{
// Sammuttaa kaikki ledit
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++){
  digitalWrite(led[i], LOW);
}
=======

void initializeLeds()
{
// see requirements for this function from leds.h
}

void setLed(byte ledNumber)
{
// see requirements for this function from leds.h

}


void clearAllLeds()
{
// see requirements for this function from leds.h
}

void setAllLeds()
{
// Sytyttää kaikki ledit
for(int i=0; i< sizeof(led) / sizeof(led[0]); i++){
  digitalWrite(led[i], HIGH);
}
}
void show1()
{
//Laskee binääreissä 0-15 käyttäen ledejä
byte count=0;
while(count<16){
  for(int i=0; i< sizeof(led) / sizeof(led[0]); i++){
digitalWrite(led[i],bitRead(count,i));
}
  count++;
  delay(500);
  }
}
void show2(int rounds)
{
//Kierrättää valot kaikki päällä vuoronperään 
int aika=1500;
for(int y=0;y<=rounds;y++){
  for(int i=0; i< sizeof(led) / sizeof(led[0]); i++){
      digitalWrite(led[i],HIGH);
      delay(aika);
      digitalWrite(led[i],LOW);
    }
    aika=aika-250;
}
if(aika<250){
  aika=250;
}
}
=======
// see requirements for this function from leds.h
}


void show1()
{
// see requirements for this function from leds.h
}

void show2(int rounds)
{
// see requirements for this function from leds.h  
}
