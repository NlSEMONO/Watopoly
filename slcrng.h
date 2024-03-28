#ifndef __SLCRNG_H__
#define __SLCRNG_H__
#include "factory.h"
#include <vector>

class SLCRng : public Factory {
    std::uniform_real_distribution<float> distribution; // range of random values that can be generated (0.0 - 1.0)
    int qPos;
    public:
        SLCRng();
        virtual Event generateEvent() override;
        virtual int eventToInt(Event e) override;
};

#endif
