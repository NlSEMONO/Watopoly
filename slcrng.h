#ifndef __SLCRNG_H__
#define __SLCRNG_H__
#include "factory.h"
#include <vector>

class SLCRng : public Factory {
    std::vector<float> rngRange;
    std::uniform_real_distribution<int> distribution;
    public:
        SLCRng();
        virtual Event generateEvent() override;
};

#endif
