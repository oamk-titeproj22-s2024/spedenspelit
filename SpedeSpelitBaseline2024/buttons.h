#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>


const byte buttonPins[] = {2,3,4,5,6};
const byte numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);

extern volatile unsigned long lastDebounceTime[numButtons];
const unsigned long debounceDelay = 150;

void initButtonsAndButtonInterrupts(void);


ISR(PCINT2_vect);
#endif
