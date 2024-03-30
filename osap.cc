#include "osap.h"
#include "player.h"

OSAP::OSAP(): Square{"Collect OSAP"} {}

OSAP::~OSAP() {}

void OSAP::giveFunds(Player* p) {
    p->setLiquidCash(p->getLiquidCash() + 200);
}
