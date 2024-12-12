#include "buttons.h"
// lisätty kommenttti uutta commitia varten
volatile unsigned long lastDebounceTime[numButtons] = {0};
volatile byte buttonNumber;
volatile bool timeToCheckGameStatus=false;
extern volatile uint8_t userNumbers[99];
extern volatile int userIndex;

void initButtonsAndButtonInterrupts() {

    for (byte i = 0; i < numButtons; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    PCICR |= (1 << PCIE2);

    for (byte i = 0; i < numButtons; i++) {
        PCMSK2 |= (1 << digitalPinToPCMSKbit(buttonPins[i]));

    }
//    PCMSK2 = B01111100; // 0x7c
}

ISR(PCINT2_vect) {
    unsigned long currentTime = millis();

    for (byte i = 0; i < numButtons; i++) {
        if ((currentTime - lastDebounceTime[i]) > debounceDelay && digitalRead(buttonPins[i]) == LOW) {
            lastDebounceTime[i] = currentTime;
            buttonNumber = buttonPins[i] - 2;
            userNumbers[userIndex] = buttonNumber;                         // = userNumbers[roundcount];
            timeToCheckGameStatus = true;
            userIndex++;
            Serial.print("Nappia ");
            Serial.print(buttonNumber);
            Serial.println(" painettu");
            break;
        }
    }
}
