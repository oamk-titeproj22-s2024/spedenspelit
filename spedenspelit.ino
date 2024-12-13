#include "leds.h"
#include "display.h"
#include "buttons.h"
#include "logic.h"

extern volatile byte buttonNumber;
extern volatile byte userIndex;
extern volatile byte randomIndex;
extern volatile uint8_t randomNumbers[99];
extern volatile uint8_t userNumbers[99];
extern volatile bool timeToCheckGameStatus;
extern volatile byte numero;
bool started = true;
extern volatile bool timeToMakeNewNumber;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(1);
  initializeLeds();
  initButtonsAndButtonInterrupts();
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

  if(timeToMakeNewNumber == true) 
  {
    timeToMakeNewNumber = false;
    numero = random(0, 4);
    setLed(numero);
    randomNumbers[randomIndex++] = numero;
    Serial.print("Arvottu numero: ");
    Serial.println(numero);
    }// Arvo uusi numero
    // Talleta arvottu numero randomNumbers-taulukkoon
    // Sytytä arvottu ledi
  }  
