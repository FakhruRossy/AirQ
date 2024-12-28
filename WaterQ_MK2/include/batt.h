#ifndef BATT_H
#define BATT_H

#include "ads_1152.h"

class BATT
{
private:
    float value;

public:
    BATT();
    ~BATT();
    float getValue();
    void updateValue(ADS1152 &ads);
};

#endif