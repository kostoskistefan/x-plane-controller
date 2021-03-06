#include <Encoder.h>

RotaryEncoder elevatorTrimEncoder(ENCODER_LEFT, ENCODER_RIGHT, RotaryEncoder::LatchMode::TWO03);

void EncoderTick()
{
    elevatorTrimEncoder.tick();
}

void InitializeEncoderInterrupts()
{
    attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), EncoderTick, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), EncoderTick, CHANGE);
}

void CheckEncoder()
{
    static int pos = 0;
    
    EncoderTick();

    int newPos = elevatorTrimEncoder.getPosition();
    if (pos != newPos)
    {
        RotaryEncoder::Direction direction = elevatorTrimEncoder.getDirection();

        if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE && elevator_trim > -1.0)
            elevator_trim -= 0.05;

        else if (direction == RotaryEncoder::Direction::CLOCKWISE && elevator_trim < 1.0)
            elevator_trim += 0.05;

        pos = newPos;
    }
}
