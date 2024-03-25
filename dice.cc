#include "factory.h"
#include "dice.h"

Dice::Dice(): Factory{} {
    possibleEvents.push_back(Event::MF1);
    possibleEvents.push_back(Event::MF2);
    possibleEvents.push_back(Event::MF3);
    possibleEvents.push_back(Event::MF4);
    possibleEvents.push_back(Event::MF5);
    possibleEvents.push_back(Event::MF6);
}

Event Dice::generateEvent() {
    std::shuffle(possibleEvents.begin(), possibleEvents.end(), rng);
    return possibleEvents[0];
}
