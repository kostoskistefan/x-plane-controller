#ifndef XPLANE_H
#define XPLANE_H

#include "definitions.h"

void Initialize();
void SetDataRef(char *dref, float value);
void SubscribeToXPlaneData();
void SendUserInputToXPlane();
void SendXPlaneDataToESP();

#endif