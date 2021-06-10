#include "definitions.h"
#include "X_Plane.h"
#include "Encoder.h"
#include "Calibration.h"
#include "Initialization.h"

void setup()
{
    InitializePins();
    InitializeSerial();
    InitializeEncoderInterrupts();
    InitializeXPlane();
    
    CalibrateSensors();
    SubscribeToXPlaneData();
}

void loop()
{
    CheckEncoder();
    SendUserInputToXPlane();
    SendXPlaneDataToESP();
}