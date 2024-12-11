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

  numero = random(0,4);
  setLed(numero);
  while(!timeToCheckGameStatus && newRound == 0) {
    
  }
  while(timeToCheckGameStatus == true) {
    checkGame();
  }
    switch(newRound) {
      case 1:
      // clearAllLeds();
      setAllLeds();
      case 2:
      clearAllLeds();
      newRound = 0;
        break;
      default:
        break;
    }
  }
