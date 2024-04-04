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
    int testing_roll1;
    int testing_roll2;
    bool testingOn = false;
    Board b;

    int handleMove(Player* p, int rollSum);
    void sendToJail(Player* p);
    int handleOwnable(Player* p, int newPos, int rollSum);
    int handleSLC(Player* p);
    int handleNeedles(Player* p);
    int handleAuction(size_t start, Square* prize);
    void printBoardAndActions(const std::string& prevCmd, int playerTurn, bool hasRolled, int moneyOwed, bool delayedMoveJail = false);
    void countResidenceGym(int code1, int code2, Player* tradee, Player* trader);

    public:
        void loadFile(std::istream& in);
        void play();
        void initPlayers();
        void setPlayers(int pCount);
        void transaction(Player *trader, std::string to_trade, std::string to_get, int playerTurn);
        void setTestingOn();

    friend std::ostream &operator<<(std::ostream &out, Game &game);    
};

#endif

std::ostream &operator<<(std::ostream &out, Game &game);
