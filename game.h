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
    std::map<Player*, int> residenceOwned;
    std::map<Player*, int> gymsOwned;
    SLCRng rngSLC;
    NeedlesRng rngNH;
    int cupsDistributed;
    int currPlayer;
    Dice dice;

    Board b;

    std::vector<Square*>& getAssets(Player* p) const;
    int handleMove(Player* p, int rollSum);
    void sendToJail(Player* p);
    int handleOwnable(Player* p, int newPos, int rollSum);
    int handleSLC(Player* p);
    int handleNeedles(Player* p);

    public:
        void loadFile(std::istream& in);
        void play();
        void initPlayers();
        void setPlayers(int pCount);
        void transaction(Player *trader, std::string to_trade, std::string to_get, int playerTurn);

    friend std::ostream &operator<<(std::ostream &out, Game &game);    
};

#endif

std::ostream &operator<<(std::ostream &out, Game &game);
