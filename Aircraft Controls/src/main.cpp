#include "Definitions.h"
#include "Initialization.h"
#include "Calibration.h"
#include "Encoder.h"
#include "X_Plane.h"

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