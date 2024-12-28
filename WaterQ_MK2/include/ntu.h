#ifndef NTU_H
#define NTU_H

#include "ads_1152.h"

class NTU
{
private:
    float value;

public:
    NTU();
    ~NTU();
    float getValue();
    void updateValue(ADS1152 &ads);
};

#endif