#ifndef __FACTORY_H__
#define __FACTORY_H__
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// every type of event that can be invoked by dice rolls, SLC and Needles Hall
enum Event {NONE, MB3, MB2, MB1, MF1, MF2, MF3, MF4, MF5, MF6, MDC_TIMS, MCOLLECT_OSAP, CM200, CM100, CM50, CP25, CP50, CP100, CP200, OUTOFTIMS, 
            GOTORCH, GOTOEV3, GOTORES, GOTODC};

class Factory {
    protected: 
        Factory();
        std::vector<Event> possibleEvents; // collection of things that can be rolled
        std::default_random_engine rng; // rng seed
    public:
        virtual ~Factory() = 0;
        virtual Event generateEvent() = 0; // function to generate possible events
        virtual int eventToInt(Event e) = 0; 
};

#endif
