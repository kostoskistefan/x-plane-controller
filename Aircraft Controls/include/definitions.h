#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <SPI.h>
#include <Filter.h>

#define XPLANE_IP "192.168.0.101"

#define PERIOD (uint8_t)80

#define ROLL_SENSOR A0
#define PITCH_SENSOR A1
#define THROTTLE_SENSOR A2
#define MIXTURE_SENSOR A3

#define ENCODER_LEFT (uint8_t)2
#define ENCODER_RIGHT (uint8_t)3

#define BUZZER_PIN (uint8_t)4

char buffer[1024];

uint32_t timer = 0;
uint16_t pitch_min = UINT16_MAX, roll_min = UINT16_MAX;
uint16_t pitch_max = 0, roll_max = 0;
float elevator_trim = 0;

ExponentialFilter<long> rollFilter(50, 0);
ExponentialFilter<long> pitchFilter(50, 0);
ExponentialFilter<long> throttleFilter(50, 0);
ExponentialFilter<long> mixtureFilter(50, 0);

#endif