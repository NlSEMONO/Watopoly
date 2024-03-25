#include "factory.h"
#include "slcrng.h"

SLCRng::SLCRng(): Factory{}, rngRange{}, distribution(0.0, 1.0) {
    // initialize possible events
    const int eventCount = 8;
    possibleEvents.push_back(Event::MB3);
    possibleEvents.push_back(Event::MB2);
    possibleEvents.push_back(Event::MB1);
    possibleEvents.push_back(Event::MF1);
    possibleEvents.push_back(Event::MF2);
    possibleEvents.push_back(Event::MF3);
    possibleEvents.push_back(Event::MDC_TIMS);
    possibleEvents.push_back(Event::MCOLLECT_OSAP);

    // probabilities of all possible events
    float probs[eventCount] = {1/(float)8, 1/(float)6, 1/(float)6, 1/(float)8, 1/(float)6, 1/(float)6, 1/(float)24, 1/(float)24};
    rngRange.push_back(probs[0]);
    for (int i = 1; i < eventCount; ++i) rngRange[i] = rngRange[i - 1] + probs[i];
}

Event SLCRng::generateEvent() {
    // determine if we get 1% out of tims
    const int outOfTimsIntervalStart = 45;
    float event = distribution(rng);
    if (outOfTimsIntervalStart <= event && event <= outOfTimsIntervalStart + 1) return Event::OUTOFTIMS;
    
    // roll again for a normal event
    event = distribution(rng);
    float left = 0;
    for (int i = 0; i < possibleEvents.size(); ++i) {
        if (left <= event && event < rngRange[i]) return possibleEvents[i];
        left = rngRange[i];
    }
    return possibleEvents[possibleEvents.size() - 1];
}

