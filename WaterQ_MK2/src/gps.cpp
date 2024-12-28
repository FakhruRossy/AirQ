#include "gps.h"

GPS::GPS() : gps(TinyGPSPlus()) {}

GPS::~GPS() {}

float GPS::getLatitude()
{
    return this->latitude;
}

float GPS::getLongitude()
{
    return this->longitude;
}

void GPS::updateData(HardwareSerial &serial)
{
    while (serial.available() > 0)
    {
        gps.encode(serial.read());
        if (gps.location.isValid())
        {
            this->latitude = gps.location.lat();
            this->longitude = gps.location.lng();
        }
    }
}