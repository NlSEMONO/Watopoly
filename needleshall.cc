#include "needleshall.h"

NeedlesHall::NeedlesHall(): Square{"Needles Hall"}, rng{} {}

NeedlesHall::~NeedlesHall() {}

Event NeedlesHall::generateEvent(int cupsGiven) {
    Event toReturn = rng.generateEvent();
    while (toReturn == Event::OUTOFTIMS && cupsGiven >= 4) {
        toReturn = rng.generateEvent();
    }
    return toReturn;
}
