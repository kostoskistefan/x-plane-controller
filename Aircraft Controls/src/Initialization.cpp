#include "Initialization.h"

void InitializePins()
{
    DDRA = 0xFF;
    DDRD &= 0b11110111;
}

void InitializeSerial()
{
    Serial.begin(115200);
    while (!Serial);
}

void InitializeEverything()
{
    InitializePins();
    InitializeSerial();
    InitializeEncoderInterrupts();
}