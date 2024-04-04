#ifndef __EXTENDEDSLCRNG_H__
#define __EXTENDEDSLCRNG_H__
#include "slcrng.h"
#include <vector>

class ExtendedSLCRng : public SLCRng {
    public:
        ExtendedSLCRng();
        virtual Event generateEvent() override;
        virtual ~ExtendedSLCRng() override;
};

#endif
