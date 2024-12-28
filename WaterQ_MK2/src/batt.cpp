#include "batt.h"

BATT::BATT() {}

BATT::~BATT() {}

void BATT::updateValue(ADS1152 &ads)
{
    this->value = ads.getValueVoltage();
}

float BATT::getValue()
{
    return this->value;
}