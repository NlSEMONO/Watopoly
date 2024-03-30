#ifndef __GYM_H__
#define __GYM_H__
#include <vector>
#include <string>
#include "player.h"
#include "square.h"

class Gym: public Square {
    Player *owner = nullptr;
    int purchase_cost;
    int gymsOwned = 0;
    bool bought = false;
    bool mortgaged = false;

    public:
    Gym(std::string name, int purchase_cost);
    

    std::string getName() const;
    Player *getOwner() const;
    int getCost() const;
    int getGymsOwned() const;
    bool isBought() const;
    bool isMortgaged() const;

    void upgrade(); // upgrading property
    void mortgage(); // mortgage
    void unmortgage(); // unmortgage
    void buy(Player *p); // buying
    void payRent(Player *payer, int diceRoll) const;

    void setOwner(Player* p);
    void setMortgaged();

    // to whoever does board, we are doing a map where each index will map to the tile we are on and its block type
};

#endif

