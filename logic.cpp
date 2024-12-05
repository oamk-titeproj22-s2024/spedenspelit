#include "logic.h"

void(* resetFunc) (void) = 0; 

  void initializeTimer() {
    TIMSK4 |= (1 << OCIE4A);
}

  void initializeGame() {
    randcount = 0;
    numero = random(3);
    randomNumbers[randcount] = numero;
    initializeTimer();
  }

void checkGame() {
  TIMSK4 &= ~(1 << OCIE4A);
  if(randcount % 10 == 0) {
    tickcount = tickcount - 6250;
  }
  numero = random(4);
  while(numero = randomNumbers[randcount]) {
    numero = random(4);
      }
  randcount++;
  numero = randomNumbers[randcount];
  TIMSK4 |= (1 << OCIE4A);
}

void startTheGame() {
  initializeGame();
  started = true;
}

ISR(TIMER4_COMPA_vect) {
  setAllLeds();
  delay(500);
  // resetFunc();
}
