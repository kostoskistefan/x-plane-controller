#ifndef TFT_H
#define TFT_H

#include <Arduino.h>
#include <TFT_eSPI.h>

class TFT {
    private:
        TFT_eSPI tft;

        void DrawValue(uint16_t x, uint8_t y, int16_t value);
        void DrawContainer(uint16_t x, uint8_t y, char *name);

    public:
        TFT() : tft(TFT_eSPI()){}

        void InitializeDisplay();
        void DrawContainers();
        void DrawValues(int index, int value);
}

#endif