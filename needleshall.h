#ifndef __NEEDLES_H__
#define __NEEDLES_H__
#include "square.h"
#include "needlesrng.h"

class NeedlesHall : public Square {
    public:
        virtual ~NeedlesHall() override;
        NeedlesHall(std::string name);
};
#endif
