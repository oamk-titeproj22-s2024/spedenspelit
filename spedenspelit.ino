#include "logic.h"
#include "leds.h"

int randomNumbers[100];
bool started = false;
int numero;
int binumero;
int randcount;
const int bin = 0b1111100;
int tickcount = 62500;

void setup() {

DDRK = 0x183;
PORTK = 0x7C;
TCCR4A = 0;
TCCR4B = 0;
TCCR4B |= 0b00000100;
OCR4A = tickcount;
initializeLeds();
setLed(1);
interrupts();
// started = false;
//digitalWrite(2, LOW);
}

void loop() {
  
if(started == false) {
//  setLed(1);
  if(PINK != bin) {
    startTheGame();
  }
}
else {
  binumero = bin & ~ (1 << (numero));
    setLed(numero);

  if(PINK == binumero) {
    checkGame();
  }

  if(PINK != binumero && PINK != bin) {
    TIMSK4 &= ~(1 << OCIE4A);
    show1();
    delay(500);
   // resetFunc();
    }
  }
}
