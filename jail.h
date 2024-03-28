#ifndef __JAIL_H_
#define __JAIL_H_
#include <map>
#include "square.h"
#include "player.h"

class Jail : public Square
{
    std::map<Player *, int> jailedTurns;

public:
    Jail();
    void sendToJail(Player *player);
    bool handleMove(Player *player);
};

#endif
