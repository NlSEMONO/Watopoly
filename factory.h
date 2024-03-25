#ifndef __FACTORY_H__
#define __FACTORY_H__
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

enum Event {NONE, MB3, MB2, MB1, MF1, MF2, MF3, MF4, MF5, MF6, MDC_TIMS, MCOLLECT_OSAP, CM200, CM100, CM50, CP25, CP50, CP100, CP200, OUTOFTIMS};

class Factory {
    protected: 
        Factory();
        std::vector<Event> possibleEvents;
        std::default_random_engine rng;
    public:
        virtual Event generateEvent() = 0;
};

#endif
