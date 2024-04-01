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
#include "dice.h"

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
    Dice dice;

    Board b;

    std::vector<Square*>& getAssets(Player* p) const;

    public:
        void loadFile(std::istream& in);
        void play();
        void initPlayers();
        void setPlayers(int pCount);

    friend std::ostream &operator<<(std::ostream &out, Game &game);    
};

#endif

std::ostream &operator<<(std::ostream &out, Game &game);
