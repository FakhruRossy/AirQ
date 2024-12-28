#ifndef ADS_1152_H
#define ADS_1152_H

#include <Adafruit_ADS1X15.h>
#include <SPI.h>

#define I2C_ADDRESS 0x48

class ADS1152
{
private:
    int value;
    byte channel;
    Adafruit_ADS1115 ads;

public:
    ADS1152();
    ~ADS1152();
    bool init(adsGain_t gain, byte channel);
    float getValueVoltage();
    float getValueADC();
};

#endif