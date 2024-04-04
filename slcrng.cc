#include "factory.h"
#include "slcrng.h"
#include <algorithm>

SLCRng::~SLCRng() {};

SLCRng::SLCRng(): Factory{}, distribution(0.0, 1.0), qPos{0} {
    // initialize possible events
    possibleEvents = {Event::MB3, Event::MB3, Event::MB3,
                        Event::MB2, Event::MB2, Event::MB2, Event::MB2, 
                        Event::MB1, Event::MB1, Event::MB1, Event::MB1, 
                        Event::MF1, Event::MF1, Event::MF1, 
                        Event::MF2, Event::MF2, Event::MF2, Event::MF2, 
                        Event::MF3, Event::MF3, Event::MF3, Event::MF3, 
                        Event::MDC_TIMS, 
                        Event::MCOLLECT_OSAP};

    // probabilities of all possible events
    std::shuffle(possibleEvents.begin(), possibleEvents.end(), rng);
}

Event SLCRng::generateEvent() {
    // determine if we get 1% out of tims
    const int outOfTimsIntervalStart = 0.45;
    float event = distribution(rng);
    if (outOfTimsIntervalStart <= event && event <= outOfTimsIntervalStart + 0.01) return Event::OUTOFTIMS;
    
    // return next card in queue
    Event toReturn = possibleEvents[qPos];
    qPos = (qPos + 1) % possibleEvents.size();
    return toReturn;
}

int SLCRng::eventToInt(Event e) { return 0; }

