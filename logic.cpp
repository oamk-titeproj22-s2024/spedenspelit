#include "logic.h"    
#include "display.h"    
#include "buttons.h"

volatile byte numero;    // viimeisin satunnaisnumero
volatile uint8_t userNumbers[99];    // painallustaulukko
volatile uint8_t randomNumbers[99];  // satunnaisnumeroiden taulukko
volatile byte userIndex = 0;     // painallustaulukon järjestysnumero 
volatile byte randomIndex = 0;   // satunnaisnumeroiden taulukon järjestysnumero
extern volatile bool timeToCheckGameStatus;    // boolean pelitilanteen tarkistamiselle
extern volatile byte buttonNumber;    // painetun napin järjestysnumero nappikirjaston taulukossa
volatile bool timeToMakeNewNumber;    // boolean uuden satunnaisnumeron luomiselle
extern volatile bool started;    // boolean pelin käynnistykselle


void initializeTimer() {
  cli();    // pysäytä kaikki aktiiviset keskeytyspalvelijat
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12); 
  OCR1A = 62500;        // 1Hz pelinopeus alussa
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer COMPA Interrupt
  sei();  // salli keskeytyspalvelijoiden toiminta
}

  void initializeGame() {
    userIndex = 0;    // nollaa painallustaulukon järjestysnumero
    randomIndex = 0;  // nollaa satunnaisnumeroiden taulukon järjestysnumero
  }
  
void checkGame() 
{
  clearAllLeds();    // sammuta kaikki ledit
      // Serial.println(userNumbers[userIndex-1]);
      // Serial.println(randomNumbers[randomIndex-1]);
      for(int i=0; i<userIndex; i++){ 
    if(userNumbers[i]!=randomNumbers[i])  
    {
    stopTheGame();   // pysäytä peli painallustaulukon erotessa satunnaisnumeroiden taulukosta
//      Serial.print("Peli päättyi, ");
//      Serial.print("Lopullinen kierrosluku: ");
//      Serial.println(userIndex);
      return;
      }  
    }
  if(userIndex == 99)
  {
    stopTheGame(); // pysäytä peli kierrosluvun ollessa 99 näyttöjen salliessa vain kaksinumeroisen kierrosluvun
    Serial.println("Voitit pelin");
    return;
  }
//  Serial.print("Oikea painallus, ");
//  Serial.print("Kierrosluku: ");
//  Serial.println(userIndex);
  showResult(userIndex);  // Näytä kierrosluku näytöillä

  if(randomIndex % 10 == 0)
  {
    OCR1A = (uint16_t)(OCR1A*0.9); //Nopeutetaan
//    Serial.print("OCR1A on ");
//    Serial.println(OCR1A);
  }
}

void startTheGame() {
  clearAllLeds();    // Sammuta ledit
  initializeTimer();   // aktivoi ajastinpohjainen keskeytysrutiini
  initializeGame();    // nollaa taulukoiden järjestysnumerot
  initializeDisplay(); // alusta näytöt
  initButtonsAndButtonInterrupts();    // alusta napit
  delay(500);    // odota 0.5 sekuntia
}

void stopTheGame(){
  started = false;    // aseta pelin käynnistystilanne epätodeksi
  TIMSK1 &=~(1<<OCIE1A);    // pysäytä ajastin
  showResult(userIndex);    // näytä kierrosluku näytöillä
  clearAllLeds();           // sammuta ledit
  setAllLeds();             // sytytä kaikki ledit
}

ISR(TIMER1_COMPA_vect) 
{
  timeToMakeNewNumber = true;
}
