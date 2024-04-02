#include "osap.h"
#include "player.h"

OSAP::OSAP(): Square{"Collect OSAP"} {}

OSAP::~OSAP() {}

void OSAP::giveFunds(Player* p) { p->changeCash(200);}
