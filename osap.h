#ifndef __OSAP_H__
#define __OSAP_H__
#include "square.h"
#include "player.h"

class OSAP : public Square {
    public:
        OSAP();
        virtual ~OSAP() override;
        void giveFunds(Player* p);
};

#endif
