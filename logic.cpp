#include "logic.h"
#include "display.h"

volatile int newRound;
volatile byte numero;
volatile uint8_t userNumbers[99];
volatile uint8_t randomNumbers[99];
volatile int userIndex = 0;
volatile int randomIndex = 0;
extern volatile bool timeToCheckGameStatus;
extern volatile byte buttonNumber;
volatile bool timeToMakeNewNumber;


void initializeTimer() {
  cli();
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12); 
  OCR1A = 62500;        // Timer Compare1A Register
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer COMPA Interrupt
  sei();
}

  void initializeGame() {
    userIndex = 0;
    randomIndex = 0;
    for(byte i=0; i<100; i++){
      userNumbers[i]=0;
      randomNumbers[i]=0;
    }
  }

void checkGame() 
{
  clearAllLeds();
   for(int i = 0; i<userIndex; i++){ 
    if(userNumbers[i]!=randomNumbers[i])
    {
      stopTheGame();
      for(byte k=0; k<10;k++){
        Serial.print("randomtable ");
        Serial.println(randomNumbers[k]); 
      }
      Serial.println("Peli päättyi");
      Serial.println(userIndex);
      Serial.println(randomIndex);
      return;
      }
   }
  if(userIndex == 99)
  {
    stopTheGame();
    Serial.println("Voitit pelin");
    return;
  }
  showResult(userIndex);

  if(userIndex % 10 == 0)
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
  initializeTimer();
  initializeGame();
}

void stopTheGame(){
  TIMSK1 &=~(1<<OCIE1A);
  showResult(userIndex);
  clearAllLeds();
  setAllLeds();
}

ISR(TIMER1_COMPA_vect) 
{
  timeToMakeNewNumber = true;
}
