#include "logic.h"
#include "display.h"

volatile int newRound;
volatile int roundcount = 0;
volatile byte numero;
volatile uint8_t userNumbers[99];
volatile uint8_t randomNumbers[99];
extern volatile bool timeToCheckGameStatus;
extern volatile byte buttonNumber;


void initializeTimer() {
  cli();
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12); // | (1 << CS10);
  OCR1A = 62500;        // Timer Compare1A Register
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer COMPA Interrupt
  sei();
}

  void initializeGame() {
    roundcount = 0;
  }

void checkGame() 
{
  for(byte i=0; i<=roundcount; i++)
  {
    if(userNumbers[i]!=randomNumbers[i])
    {
      stopTheGame();
      Serial.println(userNumbers[i]);
      Serial.println(randomNumbers[i]);
      return;
      }
  }
  if(roundcount == 99)
  {
    stopTheGame();
    return;
  }
  showResult(roundcount);

  if(roundcount % 10 == 0)
  {
    OCR1A = (uint16_t)(OCR1A*0.9); //Nopeutetaan
    Serial.print("OCR1A on ");
    Serial.println(OCR1A);
  }
}

//if(userNumbers[roundcount] == randomNumbers[roundcount]) {
//  roundcount++;
//}
//
//else {
//  clearAllLeds();
//  setAllLeds();
//}
  
//if(buttonNumber == numero) {
////  newRound = 2;
//  timeToCheckGameStatus = false;
//}
//else {
//  newRound = 1; 
//}
// 

void startTheGame() {
  roundcount = 0;
  TCNT1 = 0;
  TIMSK1 |=(1<<OCIE1A);
  Serial.println("=Peli alkaa");
}

void stopTheGame(){
  TIMSK1 &=~(1<<OCIE1A);
  showResult(roundcount);
}

ISR(TIMER1_COMPA_vect) 
{
    numero = random(0, 4);
    setLed(numero);
    randomNumbers[roundcount] = numero;
    Serial.print("Arvottu numero: ");
    Serial.println(numero);
}
  
