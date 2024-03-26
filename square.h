#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <string>
#include <vector>
#include "player.h"

class Square {
    protected:
        Square();
        std::vector<Player*> players;
    public:
        void addPlayer(Player* player); // removes all instances of player in players
        void removePlayer(Player* player); // removes all instances of player in players
};

#endif
