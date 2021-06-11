#include "Definitions.h"

char buffer[1024];

uint32_t timer = 0;
uint16_t pitch_min = UINT16_MAX, roll_min = UINT16_MAX;
uint16_t pitch_max = 0, roll_max = 0;
float elevator_trim = 0;

ExponentialFilter<long> rollFilter(50, 0);
ExponentialFilter<long> pitchFilter(50, 0);
ExponentialFilter<long> throttleFilter(50, 0);
ExponentialFilter<long> mixtureFilter(50, 0);