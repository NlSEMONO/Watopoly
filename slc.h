#ifndef __SLC_H__
#define __SLC_H__
#include "square.h"
#include "slcrng.h"

class SLC : public Square {
    public:
        virtual ~SLC() override;
        SLC(std::string name);
};
#endif
