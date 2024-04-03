#include "goosenest.h"

GooseNest::~GooseNest() {}

GooseNest::GooseNest(): Square{"Goose Nesting"}, accumulated{0} {}

int GooseNest::getAccumulated() const {return accumulated;}

void GooseNest::setAccumulated(int n) { accumulated = n; }
