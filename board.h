#ifndef __BOARD_H__
#define __BOARD_H__
#include <map>
#include <vector>
#include <memory>
#include "player.h"
#include "square.h"
#include "dice.h"

class Board {
    std::vector<std::unique_ptr<Square>> squares;
    std::map<std::string, int> nameToIndex;
    std::map<std::string, std::vector<int>> monopolies;
    std::vector<std::unique_ptr<Player>> players;
    int currentPlayer;
    Dice dice;

    public: 
        Board();
        int rollDice();
        void makeMove(Player *p);
        void addPlayer(std::string name);
};

#endif
