#ifndef __FACTORY_H__
#define __FACTORY_H__
#include <vector>

enum Event {MB3, MB2, MB1, MF1, MF2, MF3, MDC_TIMS, MCOLLECT_OSAP, CM200, CM100, CM50, CP25, CP50, CP100, CP200};

class Factory {
    std::vector<int> probabilities;
    std::vector<Event> possibleEvents;
    public:
        virtual Event generateEvent() = 0;
};

#endif
