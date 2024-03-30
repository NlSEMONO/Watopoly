#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "slcrng.h"
#include "needlesrng.h"
#include "player.h"
#include "board.h"

class Game {
    int playerCount;
    std::map<std::string, Player*> nameToPlayer;
    std::vector<std::unique_ptr<Player>> players;
    std::map<Player *, int> jailedTurns;
    std::map<Player *, int> numCups;
    SLCRng rngSLC;
    NeedlesRng rngNH;
    int cupsDistributed;
    int currPlayer;

    Board b;

    public:
        void loadFile(std::istream& in);
        void play();
        void setPlayers(int pCount);
};

#endif
