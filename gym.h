#ifndef __GYM_H__
#define __GYM_H__
#include <vector>
#include <string>
#include "player.h"
#include "square.h"

class Gym: public Square {
    Player *owner = nullptr;
    int purchase_cost;
    bool bought = false;
    bool mortgaged = false;

    public:
    Gym(std::string name, int purchase_cost);
    

    std::string getName() const;
    virtual Player *getOwner() const override;
    int getCost() const override;
    int getGymsOwned() const;
    bool isBought() const;
    int getRent(int gymsOwned, int diceRoll) const;
    virtual bool isMortgaged() const override;

    void mortgage(); // mortgage
    void unmortgage(); // unmortgage
    void buy(Player *p) override; // buying
    void payRent(Player *payer, int gymsOwned, int diceRoll) const;

    virtual void setOwner(Player* p) override;
    void setMortgaged();

    // to whoever does board, we are doing a map where each index will map to the tile we are on and its block type
};

#endif
