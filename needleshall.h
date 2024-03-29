#ifndef __NEEDLES_H__
#define __NEEDLES_H__
#include "square.h"
#include "needlesrng.h"

class NeedlesHall : public Square {
    NeedlesRng rng;
    public:
        virtual ~NeedlesHall() override;
        NeedlesHall();
        Event generateEvent(int cupsGiven);
};
#endif
