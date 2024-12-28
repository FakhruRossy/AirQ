#include "a01nyub.h"

A01NYUB::A01NYUB() {}
A01NYUB::~A01NYUB() {}

float A01NYUB::getValue()
{
    return this->value;
}

float A01NYUB::updateValue(HardwareSerial &serial, float highMax)
{
    unsigned char data[4] = {};
    do
    {
        for (int i = 0; i < 4; i++)
        {
            data[i] = serial.read();
        }
    } while (serial.read() == 0xff);

    serial.flush();

    if (data[0] == 0xff)
    {
        int sum;
        float distance;
        sum = (data[0] + data[1] + data[2]) & 0x00FF;
        if (sum == data[3])
        {
            distance = (data[1] << 8) + data[2];
            if (distance > 280)
            {
                distance /= 10; // Convert mm to cm
                serial.print(distance);
                this->value = highMax - distance; // Calculate TMA
                serial.print(this->value);
                return this->value;
            }
            else
            {
                return 0; // Below Lower Limit
            }
        }
    }
    return value;
}