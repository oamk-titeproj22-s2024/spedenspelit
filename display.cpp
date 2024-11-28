void writeByte(uint8_t bits, bool last)
{
    digitalWrite(serialInputPin, 1);
    digitalWrite(shiftClockPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(shiftClockPin, LOW);
    for (int i = 0; i < 7; i++)
    {
        digitalWrite(serialInputPin, (bits >> i) & 0x01);
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
