#include "display.h"
#include <cstdint>

const int ResetPin = 12;
    const int shiftClockPin = 11;
    const int latchClockPin = 10;
    const int outEnablePin = 9;
    const int serialInputPin = 8;

void initializeDisplay(void)
{
// See requirements for this function from display.h
}


void writeByte(uint8_t bits,bool last)
{
// See requirements for this function from display.h
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
// See requirements for this function from display.h
}

void showResult(byte number)
{
// See requirements for this function from display.h
}

