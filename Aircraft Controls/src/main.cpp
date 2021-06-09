#include "definitions.h"

/* #region Initialization */ 

void EncoderTick()
{
    elevatorTrimEncoder.tick();
}

void InitializePins()
{
    DDRA = 0xFF;
    DDRD &= 0b11110111;
}

void InitializeInterrupts()
{
    attachInterrupt(digitalPinToInterrupt(2), EncoderTick, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), EncoderTick, CHANGE);
}

void InitializeSerial()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
}

void CalibrateSensor(uint8_t pin, uint16_t &min, uint16_t &max)
{
    tone(BUZZER_PIN, 1000, 250);

    uint32_t current_time = millis();

    while (millis() < current_time + 5000)
    {
        uint16_t value = analogRead(pin);

        if (value > max)
            max = value;

        if (value < min)
            min = value;
    }
}

void Calibration()
{
    CalibrateSensor(ROLL_SENSOR, roll_min, roll_max);
    CalibrateSensor(PITCH_SENSOR, pitch_min, pitch_max);

    tone(BUZZER_PIN, 1000, 1000);
}

void Initialization()
{
    InitializePins();
    InitializeInterrupts();
    InitializeSerial();
    Ethernet.begin(mac, IPAddress(192, 168, 0, 150));
    udp.begin(UDP_PORT);
}

/* #endregion Initialization */ 

void CheckEncoder()
{
    static int pos = 0;
    elevatorTrimEncoder.tick();

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

void SendUARTDataToESP()
{
    int packetSize = udp.parsePacket();
    if (packetSize)
    {
        char *buff = &buffer[3];
        udp.read(buff, packetSize);
        String type = String(buff).substring(0, 4);

        if (type == "RREF")
        {
            for (int offset = 5; offset < packetSize; offset += 8)
            {
                int code = *((int *)(buff + offset));
                int value = (int)(*((float *)(buff + offset + 4)));

                if (code >= 0 && code < 5)
                {
                    Serial.print(code);
                    Serial.println(value);
                }
            }
        }
    }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* #region X-Plane */ 

void SendPacket(char * header, uint16_t size)
{
    udp.beginPacket(remote_ip, UDP_PORT);
    udp.write(header, size);
    udp.endPacket();
}

void SetDataRef(char *dref, float value)
{
    struct __attribute__((packed))
    {
        char dummy[3];
        char hdr[5] = "DREF";
        float dref_val;
        char dref_path[500];
    } req;

    req.dref_val = value;

    for (uint16_t x = 0; x < sizeof(req.dref_path); x++)
        req.dref_path[x] = 0x20;

    strcpy((char *)req.dref_path, (char *)dref);

    SendPacket(req.hdr, sizeof(req) - sizeof(req.dummy));
}

void SubscribeToDataRef(char *dref, uint32_t index)
{
    struct __attribute__((packed))
    {
        char dummy[3];
        char hdr[5] = "RREF";
        uint32_t dref_freq;
        uint32_t dref_index;
        char dref_path[400];
    } req;

    req.dref_freq = 2;
    req.dref_index = index;

    for (uint16_t x = 0; x < sizeof(req.dref_path); x++)
        req.dref_path[x] = 0x20;

    strcpy((char *)req.dref_path, (char *)dref);

    SendPacket(req.hdr, sizeof(req) - sizeof(req.dummy));
}

void SubscribeToXPlaneData()
{
    SubscribeToDataRef((char *)"sim/cockpit2/gauges/indicators/calibrated_airspeed_kts_pilot", 0);
    SubscribeToDataRef((char *)"sim/cockpit2/gauges/indicators/heading_electric_deg_mag_pilot", 1);
    SubscribeToDataRef((char *)"sim/cockpit2/gauges/indicators/altitude_ft_pilot", 2);
    SubscribeToDataRef((char *)"sim/cockpit2/gauges/indicators/vvi_fpm_pilot", 3);
    SubscribeToDataRef((char *)"sim/cockpit2/engine/indicators/engine_speed_rpm[0]", 4);
}

void SendInputToXPlane()
{
    if (millis() > timer + PERIOD)
    {
        rollFilter.Filter(analogRead(ROLL_SENSOR));
        pitchFilter.Filter(analogRead(PITCH_SENSOR));
        throttleFilter.Filter(analogRead(THROTTLE_SENSOR));
        mixtureFilter.Filter(analogRead(MIXTURE_SENSOR));

        float yoke_roll = mapfloat(rollFilter.Current(), roll_min, roll_max, -1, 1);
        float yoke_pitch = mapfloat(pitchFilter.Current(), pitch_min, pitch_max, 1, -1);

        float throttle = mapfloat(throttleFilter.Current(), 0, 1023, 0, 1);
        float mixture = mapfloat(mixtureFilter.Current(), 0, 1023, 0, 1);

        SetDataRef((char *)"sim/cockpit2/controls/yoke_roll_ratio", yoke_roll);
        SetDataRef((char *)"sim/cockpit2/controls/yoke_pitch_ratio", yoke_pitch);
        SetDataRef((char *)"sim/cockpit2/controls/elevator_trim", elevator_trim);
        SetDataRef((char *)"sim/flightmodel/engine/ENGN_thro[0]", throttle);
        SetDataRef((char *)"sim/flightmodel/engine/ENGN_mixt[0]", mixture);
    }
}

/* #endregion X-Plane */ 

void setup()
{
    Initialization();
    Calibration();
    SubscribeToXPlaneData();
}

void loop()
{
    CheckEncoder();
    SendUARTDataToESP();
    SendInputToXPlane();
}