#ifndef __NEEDLESRNG_H__
#define __NEEDLESRNG_H__
#include "factory.h"
#include <vector>

class NeedlesRng : public Factory {
    std::vector<float> rngRange;
    std::uniform_real_distribution<int> distribution;
    public:
        NeedlesRng();
        virtual Event generateEvent() override;
};

#endif
