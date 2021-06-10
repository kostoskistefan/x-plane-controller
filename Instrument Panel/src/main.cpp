#include "TFT.h"

TFT tft;

void InitializeSerial()
{
    Serial2.begin(115200, SERIAL_8N1, 16, 17);
    while (!Serial2);
}

void setup()
{
    InitializeSerial();
    tft.InitializeDisplay();
    tft.DrawContainers();
}

void loop()
{
    if (Serial2.available() > 0)
    {
        String received = Serial2.readStringUntil('\n');

        int dataRefIndex = received.charAt(0) - '0';
        int dataRefValue = received.substring(1).toInt();

        tft.DrawValues(dataRefIndex, dataRefValue);
    }
}
