#include "leds.h"
#include "display.h"
#include "buttons.h"
#include "logic.h"

extern volatile byte buttonNumber;
extern volatile byte newRound;
extern volatile bool timeToCheckGameStatus;
extern int numero;
int roundcount;
bool started = true;

void setup() {
  // put your setup code here, to run once:
  initializeLeds();
  initButtonsAndButtonInterrupts();
}

void(* resetFunc) (void) = 0;

void loop() {
unsigned long aikavali = millis();

while (started != true) {
  show1();
}

  numero = random(4);
  setLed(numero-1);
  while(!timeToCheckGameStatus) {
    
  }
  if(timeToCheckGameStatus == true) {
    checkGame();
  }
    switch(newRound) {
      case 1:
      clearAllLeds();
      setAllLeds();
        break;
      case 2:
      clearAllLeds();
        break;
      default:
        break;
    }
  }
