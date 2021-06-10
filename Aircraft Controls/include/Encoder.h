#ifndef ENCODER_H
#define ENCODER_H

#include "definitions.h"
#include <RotaryEncoder.h>

RotaryEncoder elevatorTrimEncoder(ENCODER_LEFT, ENCODER_RIGHT, RotaryEncoder::LatchMode::TWO03);

void InitializeEncoderInterrupts();
void CheckEncoder();

#endif