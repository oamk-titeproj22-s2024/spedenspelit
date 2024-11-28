#include "buttons.h"

volatile unsigned long lastDebounceTime[numButtons] = {0};

void initButtonsAndButtonInterrupts() {
    for (byte i = 0; i < numButtons; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    PCICR |= (1 << PCIE2);

    for (byte i = 0; i < numButtons; i++) {
        PCMSK2 |= (1 << digitalPinToPCMSKbit(buttonPins[i])); 

    }
    PCMSK2 = B01111100; // 0x7c
}

ISR(PCINT2_vect) {
    unsigned long currentTime = millis();

    for (byte i = 0; i < numButtons; i++) {
        if ((currentTime - lastDebounceTime[i]) > debounceDelay && digitalRead(buttonPins[i]) == LOW) {
            lastDebounceTime[i] = currentTime;
            Serial.print("Nappia ");
            Serial.print(buttonPins[i]);
            Serial.println(" painettu");
        }
    }
}
