#include "factory.h"
#include "needlesrng.h"

NeedlesRng::NeedlesRng(): Factory{}, rngRange{}, distribution(0.0, 1.0) {
    // initialize possible events
    const int eventCount = 7;
    possibleEvents.push_back(Event::CM200);
    possibleEvents.push_back(Event::CM100);
    possibleEvents.push_back(Event::CM50);
    possibleEvents.push_back(Event::CP25);
    possibleEvents.push_back(Event::CP50);
    possibleEvents.push_back(Event::CP100);
    possibleEvents.push_back(Event::CP200);

    // probabilities of all possible events
    float probs[eventCount] = {1/(float)18, 1/(float)9, 1/(float)6, 1/(float)3, 1/(float)6, 1/(float)9, 1/(float)18};
    rngRange.push_back(probs[0]);
    for (int i = 1; i < eventCount; ++i) rngRange[i] = rngRange[i - 1] + probs[i];
}

Event NeedlesRng::generateEvent() {
    // determine if we get 1% out of tims
    const int outOfTimsIntervalStart = 69;
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

