#ifndef GPS_H
#define GPS_H

#include <TinyGPSPlus.h>

class GPS
{
private:
    float latitude;
    float longitude;

    TinyGPSPlus gps;

public:
    GPS();
    ~GPS();

    void updateData(HardwareSerial &serial);
    float getLatitude();
    float getLongitude();
};

#endif