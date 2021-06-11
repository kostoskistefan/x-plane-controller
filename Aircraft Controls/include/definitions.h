#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#pragma once

#include <Arduino.h>
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

extern char buffer[1024];

extern uint32_t timer;
extern uint16_t pitch_min, roll_min;
extern uint16_t pitch_max, roll_max;
extern float elevator_trim;

extern ExponentialFilter<long> rollFilter;
extern ExponentialFilter<long> pitchFilter;
extern ExponentialFilter<long> throttleFilter;
extern ExponentialFilter<long> mixtureFilter;

#endif