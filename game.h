#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <vector>
#include <memory>
#include "slcrng.h"
#include "needlesrng.h"
#include "player.h"

class Game {
    int playerCount;
    std::vector<std::unique_ptr<Player>> players;
    SLCRng rngSLC;
    NeedlesRng rngNH;
    int cupsDistributed;
    public:
        void loadFile(std::istream& in);
        void play();
        void setPlayers(int pCount);
};

#endif
