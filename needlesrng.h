#ifndef __NEEDLESRNG_H__
#define __NEEDLESRNG_H__
#include "factory.h"
#include <vector>

class NeedlesRng : public Factory {
    std::uniform_real_distribution<float> distribution; // range of random values that can be generated (0.0 - 1.0)
    int qPos;
    public:
        NeedlesRng();
        virtual Event generateEvent() override;
        virtual int eventToInt(Event e) override;
        virtual ~NeedlesRng() override;
        
};

#endif
