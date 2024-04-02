#include "goosenest.h"

GooseNest::~GooseNest() {}

GooseNest::GooseNest(): Square{"Goose Nesting"} {}

int GooseNest::getAccumulated() const {return accumulated;}

void GooseNest::setAccumulated(int n) { accumulated = n; }
