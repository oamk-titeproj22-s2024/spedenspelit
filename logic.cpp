#include "logic.h"
#include "display.h"
#include "buttons.h"

volatile byte numero;
volatile uint8_t userNumbers[99];
volatile uint8_t randomNumbers[99];
volatile byte userIndex = 0;
volatile byte randomIndex = 0;
extern volatile bool timeToCheckGameStatus;
extern volatile byte buttonNumber;
volatile bool timeToMakeNewNumber;
extern volatile bool started;


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
  }
  
void checkGame() 
{
  clearAllLeds();
      Serial.println(userNumbers[userIndex-1]);
      Serial.println(randomNumbers[randomIndex-1]);
      for(int i=0; i<userIndex; i++){ 
    if(userNumbers[i]!=randomNumbers[i])  
    {
    stopTheGame();
      Serial.println("Peli päättyi");
      return;
      }  
    }
  if(userIndex == 99)
  {
    stopTheGame();
    Serial.println("Voitit pelin");
    return;
  }
  Serial.println("Oikea painallus");
  showResult(userIndex);

  if(randomIndex % 10 == 0)
  {
    OCR1A = (uint16_t)(OCR1A*0.9); //Nopeutetaan
    Serial.print("OCR1A on ");
    Serial.println(OCR1A);
  }
}

void startTheGame() {
  setAllLeds();
  delay(100);
  clearAllLeds();
  initializeTimer();
  initializeGame();
  initButtonsAndButtonInterrupts();
}

void stopTheGame(){
  started = false;
  TIMSK1 &=~(1<<OCIE1A);
  showResult(userIndex);
  clearAllLeds();
  setAllLeds();
}

ISR(TIMER1_COMPA_vect) 
{
  timeToMakeNewNumber = true;
}
