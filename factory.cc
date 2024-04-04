#include "factory.h"

Factory::Factory(): possibleEvents{}, rng{std::chrono::system_clock::now().time_since_epoch().count()} {};

Factory::~Factory() {};
