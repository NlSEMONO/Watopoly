#ifndef __DICE_H__
#define __DICE_H__
#include "factory.h"

class Dice : public Factory {
    public:
        Dice();
        virtual Event generateEvent() override;
};

#endif
