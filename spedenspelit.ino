#include "leds.h"  // sisällytä LED-kirjasto projektista
#include "display.h"  // sisällytä näyttökirjasto projektista
#include "buttons.h"  // sisällytä nappikirjasto projektista
#include "logic.h"    // sisällytä logiikkakirjasto projektista

volatile bool started = false;   // boolean pelin käynnistystä varten
extern volatile byte buttonNumber;  // muuttuja painetulle napille
extern volatile byte userIndex;  // muuttuja painallusten määrälle
extern volatile byte randomIndex;  // muuttuja luotujen satunnaisnumeroiden määrälle
extern volatile uint8_t randomNumbers[99];  // taulukko satunnaisnumeroille
extern volatile uint8_t userNumbers[99];  // taulukko painetuille napeille
extern volatile bool timeToCheckGameStatus;  // boolean pelitilanteen tarkistamiselle
extern volatile byte numero;  // viimeisin satunnaisnumero
extern volatile bool timeToMakeNewNumber;  // boolean uuden satunnaisnumeron luontia varten
extern volatile unsigned long lastButtonPressTime;  //  muuttuja viimeisimmän pelinopeuden tallentamista varten.
const unsigned long timeDuration = 2000; 
unsigned long timeElapsed = millis();
 

void setup() {
  Serial.begin(9600);  // Avaa sarjaportti mahdollista viankorjausta varten
  randomSeed(analogRead(A0));  // Paranna satunnaisuutta ottamalla arvo A0-pinnin ADC-muuntimesta
  initializeLeds();  // kutsu LED-kirjastosta ledien initialisaatiofunktiota
  initializeStartButton();  // initialisoi logiikkafunktiosta käynnistysnapin painalluspohjainen keskeytyspalvelija
  }


void loop() 
{

if(started==false)
{
  show1();  // laske binääriluvuilla 0-15 käyttäen ledejä odottaessa pelin käynnistymistä
}
else{

  if(timeToCheckGameStatus) 
  {
    timeToCheckGameStatus = false;  // heitä boolean suoraan epätodeksi tarkistuslauseen käynnistymisen jälkeen
    // Serial.println("aika katsoa status");
    checkGame();  // kutsu logiikkakirjastosta tarkistusfunktiota
  }

  if(timeToMakeNewNumber == true) 
  {
    timeToMakeNewNumber = false;   // heitä boolean suoraan epätodeksi tarkistuslauseen käynnistymisen jälkeen
    numero = random(0, 4);   // arvo uusi satunnaisnumero
    setLed(numero);  // sytytä satunnaisnumeron arpoma LED (LED-taulukon järjestysnumeron mukaan)
    randomNumbers[randomIndex++] = numero;   // tallenna uusi satunnaisnumero satunnaisnumeroiden taulukkoon
    // Serial.print("Arvottu numero: ");  // viankorjausta sarjakonsolilla
    // Serial.println(numero);
   
//    if(millis() - lastButtonPressTime > timeDuration)
//    {
//      stopTheGame();
//    }
  }  
}
}
