#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Ethernetudp.h>
#include <RotaryEncoder.h>
#include <Filter.h>

#define UDP_PORT (uint16_t)49000
#define PERIOD (uint8_t)80

#define ROLL_SENSOR A0
#define PITCH_SENSOR A1
#define THROTTLE_SENSOR A2
#define MIXTURE_SENSOR A3
#define BUZZER_PIN (uint8_t)4

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char remote_ip[] = "192.168.0.101";

EthernetUDP udp;

RotaryEncoder elevatorTrimEncoder(2, 3, RotaryEncoder::LatchMode::TWO03);
float elevator_trim = 0;

char buffer[1024];

uint32_t timer = 0;
uint16_t pitch_min = UINT16_MAX, roll_min = UINT16_MAX;
uint16_t pitch_max = 0, roll_max = 0;

ExponentialFilter<long> rollFilter(50, 0);
ExponentialFilter<long> pitchFilter(50, 0);
ExponentialFilter<long> throttleFilter(50, 0);
ExponentialFilter<long> mixtureFilter(50, 0);

#endif