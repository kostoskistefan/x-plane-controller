#ifndef XPLANE_H
#define XPLANE_H

#include "definitions.h"
#include <Ethernet.h>
#include <EthernetUdp.h>

#define UDP_PORT (uint16_t)49000

EthernetUDP udp;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// char remote_ip[] = XPLANE_IP;

typedef struct __attribute__((packed))
{
    char dummy[3];
    char hdr[5] = "DREF";
    float dref_val;
    char dref_path[500] = {0x20};
} DREF;

typedef struct __attribute__((packed))
{
    char dummy[3];
    char hdr[5] = "RREF";
    uint32_t dref_freq;
    uint32_t dref_index;
    char dref_path[400] = {0x20};
} RREF;

void InitializeXPlane();
void SetDataRef(char *dref, float value);
void SubscribeToXPlaneData();
void SendUserInputToXPlane();
void SendXPlaneDataToESP();

#endif