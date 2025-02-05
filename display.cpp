#include <Arduino.h>
#include "display.h"
const int ResetPin = 12;
const int shiftClockPin = 11;
const int latchClockPin = 10;
const int outEnablePin = 9;
const int serialInputPin = 8;

const uint8_t numerot[10] = 
{
    0b01111110, // 0
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
    digitalWrite(serialInputPin, 1);
    digitalWrite(shiftClockPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(shiftClockPin, LOW);
    for (int n = 0; n < 7; n++)
    {
        digitalWrite(serialInputPin, (bits >> n) & 0x01);
        digitalWrite(shiftClockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(shiftClockPin, LOW);
    }

    if (last)
    {
        digitalWrite(latchClockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(latchClockPin, LOW);
    }
}


void writeHighAndLowNumber(uint8_t tens, uint8_t ones)
{
    writeByte(numerot[tens], false);
    writeByte(numerot[ones], true);
}


void showResult(byte result)
{

    uint8_t tens = result / 10;
    uint8_t ones = result % 10;

    writeHighAndLowNumber(tens, ones);
}
