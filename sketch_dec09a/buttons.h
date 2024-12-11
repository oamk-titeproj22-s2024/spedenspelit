#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// Kommentti lisätty commitia varten

const byte buttonPins[] = {2,3,4,5};
const byte numButtons =  4; //sizeof(buttonPins) / sizeof(buttonPins[0]);

extern volatile unsigned long lastDebounceTime[numButtons];
const unsigned long debounceDelay = 75;

void initButtonsAndButtonInterrupts(void);


ISR(PCINT2_vect);
#endif
