#ifndef __NEEDLESRNG_H__
#define __NEEDLESRNG_H__
#include "factory.h"
#include <vector>

class NeedlesRng : public Factory {
    std::vector<float> rngRange; // breakpoints that mark right endpoint of each event 
    std::uniform_real_distribution<float> distribution; // range of random values that can be generated (0.0 - 1.0)
    public:
        NeedlesRng();
        virtual Event generateEvent() override;
};

#endif
