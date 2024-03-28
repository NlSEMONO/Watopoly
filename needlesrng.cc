#include "factory.h"
#include "needlesrng.h"
#include <algorithm>

NeedlesRng::NeedlesRng(): Factory{}, distribution((float)0, (float)1), qPos{0} {
    // initialize possible events
    possibleEvents = {Event::CM200, 
                        Event::CM100, Event::CM100, 
                        Event::CM50, Event::CM50, Event::CM50, 
                        Event::CP25, Event::CP25, Event::CP25, Event::CP25, Event::CP25, Event::CP25, 
                        Event::CP50, Event::CP50, Event::CP50, 
                        Event::CP100, Event::CP100, 
                        Event::CP200};

    // probabilities of all possible events
    std::shuffle(possibleEvents.begin(), possibleEvents.end(), rng);
}

Event NeedlesRng::generateEvent() {
    // determine if we get 1% out of tims
    const float outOfTimsIntervalStart = 0.69;
    float event = distribution(rng);
    if (outOfTimsIntervalStart <= event && event <= outOfTimsIntervalStart + 0.01) return Event::OUTOFTIMS;
    
    // return next card in queue
    Event toReturn = possibleEvents[qPos];
    qPos = (qPos + 1) % possibleEvents.size();
    return toReturn;
}

int NeedlesRng::eventToInt(Event e) {return 0; }
