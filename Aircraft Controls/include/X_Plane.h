#ifndef XPLANE_H
#define XPLANE_H

#pragma once

#include "Definitions.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define UDP_PORT (uint16_t)49000

void InitializeXPlane();
void SetDataRef(char *dref, float value);
void SubscribeToXPlaneData();
void SendUserInputToXPlane();
void SendXPlaneDataToESP();

#endif