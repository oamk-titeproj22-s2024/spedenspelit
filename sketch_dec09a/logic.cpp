#include "logic.h"

volatile byte newRound;
volatile int randcount;
volatile int numero;
extern volatile bool timeToCheckGameStatus;
extern volatile byte buttonNumber;


  void initializeGame() {
    numero = random(3);
    randomNumbers[randcount] = numero;
  }

void checkGame() {
if(buttonNumber == numero) {
  newRound = 2;
  timeToCheckGameStatus = false;
}
else {
  newRound = 1; // Aseta newRoundin
  setAllLeds(); 
}
 
  }

void startTheGame() {
  initializeGame();
}

//ISR(TIMER4_COMPA_vect) {
//  setAllLeds();
////  resetFunc();
//}
