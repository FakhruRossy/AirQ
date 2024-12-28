#ifndef SERIAL_COMS_H
#define SERIAL_COMS_H

#include <Arduino.h>

class A01NYUB
{
private:
    float value;

public:
    A01NYUB();
    ~A01NYUB();

    float getValue();
    float updateValue(HardwareSerial &serial,float highMax);
};

#endif