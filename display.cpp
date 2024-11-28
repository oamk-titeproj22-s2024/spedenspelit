// Pin-määrittelyt
#include <arduino.h>
#include "display.h"
const int ResetPin = 12;
const int shiftClockPin = 11;
const int latchClockPin = 10;
const int outEnablePin = 9;
const int serialInputPin = 8;

const byte number[10] = {
    0b11111110, // 0
    0b00110000, // 1
    0b01101101, // 2
    0b01111001, // 3
    0b00110011, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011  // 9

};

void initializeDisplay(void)
{
    pinMode(ResetPin, OUTPUT);
    pinMode(shiftClockPin, OUTPUT);
    pinMode(latchClockPin, OUTPUT);
    pinMode(outEnablePin, OUTPUT);
    pinMode(serialInputPin, OUTPUT);

    digitalWrite(ResetPin, HIGH);
    digitalWrite(outEnablePin, LOW);
    digitalWrite(latchClockPin, LOW);
}

void writeByte(uint8_t bits, bool last)
{
    for (int i = 0; i < 7; i++)
    {
        digitalWrite(serialInputPin, (bits >> i) & 0x01); // Kirjoita bitti
        digitalWrite(shiftClockPin, HIGH);               // Kellosignaali
        digitalWrite(shiftClockPin, LOW);
    }

    if (last)
    {
        digitalWrite(latchClockPin, HIGH);
        digitalWrite(latchClockPin, LOW);
    }
}


void writeHighAndLowNumber(uint8_t tens, uint8_t ones)
{
    writeByte(numerot[tens], false);
    writeByte(numerot[ones], true); 
}


void showResult(byte number) 
{
    uint8_t tens = (number / 10)-(number % 10); 
    uint8_t ones = number % 10;  

    writeHighAndLowNumber(tens, ones); 
}
