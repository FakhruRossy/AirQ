#include "ads_1152.h"

ADS1152::ADS1152() : ads(Adafruit_ADS1115()) {}

ADS1152::~ADS1152() {}

bool ADS1152::init(adsGain_t gain, byte channel)
{
    ads.setGain(gain);       // Set the gain to the private variable
    this->channel = channel; // Set the channel to the private variable
    if (!ads.begin())
    {
        return false;
    }
    return true;
}

float ADS1152::getValueVoltage()
{
    float data = ads.readADC_SingleEnded(channel); // Read the ADC value from the channel
    return ads.computeVolts(data);
}

float ADS1152::getValueADC()
{
    return ads.readADC_SingleEnded(channel); // Read the ADC value from the channel
}
