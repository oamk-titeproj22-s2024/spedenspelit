#include "buttons.h"
#include "logic.h"
// lisätty kommenttti uutta commitia varten
volatile unsigned long lastDebounceTime[numButtons] = {0};
volatile unsigned long lastDebounceTime2 = 0;
volatile byte buttonNumber;
volatile bool timeToCheckGameStatus=false;
extern volatile uint8_t userNumbers[99];
extern volatile byte userIndex;
volatile unsigned long lastButtonPressTime = 0;
extern volatile bool started;

void initButtonsAndButtonInterrupts() {

    for (byte i = 0; i < numButtons; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    PCICR |= (1 << PCIE2);

    for (byte i = 0; i < numButtons; i++) {
        PCMSK2 |= (1 << digitalPinToPCMSKbit(buttonPins[i]));

    }
}

void initializeStartButton(){

  pinMode(13, INPUT_PULLUP);
  
  PCICR |= (1 << PCIE0);

  PCMSK0 |= (1 << PCINT5);

  sei();
}

ISR(PCINT0_vect) {
  unsigned long currentTime2 = millis();
  if((currentTime2 - lastDebounceTime2) > debounceDelay){
    lastDebounceTime2 = currentTime2;
    started = !started; 
    startTheGame();
  }
}

ISR(PCINT2_vect) {
    unsigned long currentTime = millis();

    for (byte i = 0; i < numButtons; i++) {
        if ((currentTime - lastDebounceTime[i]) > debounceDelay && digitalRead(buttonPins[i]) == LOW) {
            lastDebounceTime[i] = currentTime;
            buttonNumber = buttonPins[i] - 2;
            userNumbers[userIndex] = buttonNumber;                        
            timeToCheckGameStatus = true;
            userIndex++;
            lastButtonPressTime = millis();
            Serial.print("Nappia ");
            Serial.print(buttonNumber);
            Serial.println(" painettu");
            
            }
            break;
    }
}
