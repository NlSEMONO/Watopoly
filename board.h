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
    bool isType(std::string type, int buildingCode);
    // std::vector<std::unique_ptr<Player>> players;
    // int currentPlayer;
    // Dice dice;

    public: 
        Board();
        // int rollDice();
        // void makeMove(Player *p);
        // void addPlayer(std::string name);
        void initBuilding(std::string name, Player* owner, int upgrades);
        Square *getSquare(std::string name);
        Square *getSquare(int buildingCode);
        int getIndex(std::string name);
        void getOwnedSquares(Player* owner, std::vector<Square *>& dest) const;
        bool isOwnable(int buildingCode);
        bool isAcademic(int buildingCode);
        bool isGym(int buildingCode);
        bool isResidence(int buildingCode);
        void saveProperties(ostream& out);
};

#endif
