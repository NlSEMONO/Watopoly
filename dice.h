#ifndef __DICE_H__
#define __DICE_H__
#include "factory.h"

class Dice : public Factory {
    public:
        Dice();
        virtual Event generateEvent() override;
        virtual int eventToInt(Event e) override;
        virtual ~Dice() override;
};

#endif
