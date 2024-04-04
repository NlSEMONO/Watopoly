#include "factory.h"
#include "dice.h"

Dice::~Dice() {}

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

int Dice::eventToInt(Event e) {
	if (e == Event::MF1){
		return 1;
	} else if (e == Event::MF2) {
		return 2;
	} else if (e == Event::MF3) {
		return 3;
	} else if (e == Event::MF4) {
		return 4;
	} else if (e == Event::MF5) {
		return 5;
	} else if (e == Event::MF6) {
		return 6;
	}
	return -1;
}
