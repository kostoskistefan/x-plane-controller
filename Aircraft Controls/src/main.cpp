#include "definitions.h"

void setup()
{
    InitializeEverything();
    CalibrateSensors();
    SubscribeToXPlaneData();
}

void loop()
{
    CheckEncoder();
    SendUserInputToXPlane();
    SendXPlaneDataToESP();
}