#include "ntu.h"

NTU::NTU() {}

NTU::~NTU() {}

float NTU::getValue()
{
    return this->value;
}

void NTU::updateValue(ADS1152 &ads)
{
    float voltage = ads.getValueVoltage();
    // value = (-1120 * voltage * voltage + 5740 * voltage - 4352.9); // Documentation from web, idc if it's wrong
    this->value = voltage;
}