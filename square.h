#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <string>
#include <vector>
#include "player.h"

class Player;

class Square {
    protected:
        std::string name;
        Square(std::string name);
        std::vector<Player*> players;
    public:
        void addPlayer(Player* player); // removes all instances of player in players
        void removePlayer(Player* player); // removes all instances of player in players
        virtual Player* getOwner() const;
        std::string getName() const;
        virtual ~Square() = 0;
        std::string printPlayers();
        virtual void setOwner(Player *player);
        virtual bool isMortgaged() const;
        virtual void buy(Player* p);
        virtual int getCost() const;
};

#endif
