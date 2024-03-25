#ifndef __SLCRNG_H__
#define __SLCRNG_H__
#include "factory.h"
#include <vector>

class SLCRng : public Factory {
    std::vector<float> rngRange; // breakpoints that mark right endpoint of each event 
    std::uniform_real_distribution<int> distribution; // range of random values that can be generated (0.0 - 1.0)
    public:
        SLCRng();
        virtual Event generateEvent() override;
};

#endif
