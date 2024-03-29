#include "slc.h"

SLC::SLC(): Square{"SLC"}, rng{} {}

SLC::~SLC() {}

Event SLC::generateEvent(int cupsGiven) {
    Event toReturn = rng.generateEvent();
    while (toReturn == Event::OUTOFTIMS && cupsGiven >= 4) {
        toReturn = rng.generateEvent();
    }
    return toReturn;
}
