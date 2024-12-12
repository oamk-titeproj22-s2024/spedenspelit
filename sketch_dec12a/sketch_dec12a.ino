#include "leds.h"
#include "display.h"
#include "buttons.h"
#include "logic.h"

extern volatile byte buttonNumber;
extern volatile int newRound;
extern volatile uint8_t userNumbers[99];
extern volatile int roundcount;
extern volatile bool timeToCheckGameStatus;
extern byte numero;
bool started = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(millis());
  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeTimer();
  startTheGame();
}


void loop() 
{
  if(timeToCheckGameStatus) 
  {
    timeToCheckGameStatus = false;
    Serial.println("aika katsoa status");
    checkGame();
  }

//  if(timeToMakeNewNumber == true) 
//  {
//    // timeToMakeNewNumber = false;
//    // Arvo uusi numero
//    // Talleta arvottu numero randomNumbers-taulukkoon
//    // Sytytä arvottu ledi
//  }  
}
