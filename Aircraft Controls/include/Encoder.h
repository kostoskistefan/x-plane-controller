#ifndef ENCODER_H
#define ENCODER_H

#pragma once

#include "Definitions.h"
#include <RotaryEncoder.h>

extern RotaryEncoder elevatorTrimEncoder;

void InitializeEncoderInterrupts();
void CheckEncoder();

#endif