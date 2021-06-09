#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void InitializeSerial()
{
    Serial2.begin(115200, SERIAL_8N1, 16, 17);
    while (!Serial2)
    {
    }
}

void InitializeDisplay()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_NAVY);
    tft.setTextColor(TFT_WHITE, TFT_NAVY);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
}

void DrawValue(uint16_t x, uint8_t y, int16_t value)
{
    tft.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
    tft.setTextSize(3);
    tft.drawNumber(value, x + 76, y + 47);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_NAVY);
}

void DrawContainer(uint16_t x, uint8_t y, char *name)
{
    tft.setTextPadding(tft.textWidth("99999999"));
    tft.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
    tft.fillRoundRect(x, y, 150, 70, 8, TFT_LIGHTGREY);
    tft.drawRoundRect(x, y, 150, 70, 8, TFT_WHITE);
    tft.drawString(name, x + 75, y + 15);
}

void DrawContainers()
{
    DrawContainer(5, 5, (char *)"Airspeed");
    DrawContainer(5, 80, (char *)"Heading");
    DrawContainer(160, 5, (char *)"Altitude");
    DrawContainer(160, 80, (char *)"V-Speed");
    DrawContainer(80, 155, (char *)"RPM");
}

void DrawValues(int index, int value)
{
    if (index <= 1)
        DrawValue(5, 5 + (index * 75), value);

    else if (index <= 3)
        DrawValue(160, 5 + ((index - 2) * 75), value);

    else
        DrawValue(80, 155, value);
}

void setup()
{
    InitializeSerial();
    InitializeDisplay();
    DrawContainers();
}

void loop()
{
    if (Serial2.available() > 0)
    {
        String received = Serial2.readStringUntil('\n');

        int dataRefIndex = received.charAt(0) - '0';
        int dataRefValue = received.substring(1).toInt();

        DrawValues(dataRefIndex, dataRefValue);
    }
}
