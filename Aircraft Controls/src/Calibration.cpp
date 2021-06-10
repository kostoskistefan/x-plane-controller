#include "Calibration.h"

void CalibrateSensor(uint8_t pin, uint16_t &min, uint16_t &max)
{
    tone(BUZZER_PIN, 1000, 250);

    uint32_t current_time = millis();

    while (millis() < current_time + 5000)
    {
        uint16_t value = analogRead(pin);

        if (value > max)
            max = value;

        if (value < min)
            min = value;
    }
}

void CalibrateSensors()
{
    CalibrateSensor(ROLL_SENSOR, roll_min, roll_max);
    CalibrateSensor(PITCH_SENSOR, pitch_min, pitch_max);

    tone(BUZZER_PIN, 1000, 1000);
}