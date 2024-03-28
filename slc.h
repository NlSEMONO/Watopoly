#include "square.h"
#include "slcrng.h"

class SLC : public Square {
    SLCRng rng;
    public:
        virtual ~SLC() override;
        SLC();
        Event generateEvent(int cupsGiven);
};