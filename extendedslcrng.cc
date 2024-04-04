#include "slcrng.h"
#include "extendedslcrng.h"
#include <vector>

ExtendedSLCRng::~ExtendedSLCRng() {}

ExtendedSLCRng::ExtendedSLCRng() : SLCRng{} {
    possibleEvents.push_back(Event::GOTORCH);
    possibleEvents.push_back(Event::GOTORCH);
    possibleEvents.push_back(Event::GOTOEV3);
    possibleEvents.push_back(Event::GOTOEV3);
    possibleEvents.push_back(Event::GOTORES);
    possibleEvents.push_back(Event::GOTORES);
    possibleEvents.push_back(Event::GOTODC);
    possibleEvents.push_back(Event::GOTODC);

    std::shuffle(possibleEvents.begin(), possibleEvents.end(), rng);
}

Event ExtendedSLCRng::generateEvent() {
    return SLCRng::generateEvent();
}
