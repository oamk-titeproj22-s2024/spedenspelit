#include "leds.h"
#include "display.h"
#include "buttons.h"
#include "logic.h"

volatile bool started = false;
extern volatile byte buttonNumber;
extern volatile byte userIndex;
extern volatile byte randomIndex;
extern volatile uint8_t randomNumbers[99];
extern volatile uint8_t userNumbers[99];
extern volatile bool timeToCheckGameStatus;
extern volatile byte numero;
extern volatile bool timeToMakeNewNumber;
extern volatile unsigned long lastButtonPressTime;  
const unsigned long timeDuration = 2000; 
unsigned long timeElapsed = millis();
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  initializeLeds();
  initializeStartButton();
  }


void loop() 
{

if(started==false)
{
  show1();
}
else{

  if(timeToCheckGameStatus) 
  {
    timeToCheckGameStatus = false;
    // Serial.println("aika katsoa status");
    checkGame();
  }

  if(timeToMakeNewNumber == true) 
  {
    timeToMakeNewNumber = false;
    numero = random(0, 4);
    setLed(numero);
    randomNumbers[randomIndex++] = numero;
    // Serial.print("Arvottu numero: ");
    // Serial.println(numero);
   
//    if(millis() - lastButtonPressTime > timeDuration)
//    {
//      stopTheGame();
//    }
  }  
}
}
