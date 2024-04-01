#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__
#include <vector>
#include <string>
#include "player.h"
#include "square.h"

class Residence: public Square {
    std::string name;
    int purchase_cost;
    int residences_owned = 0;
    std::vector<int> rentMoney;
    bool bought = false;
    bool mortgaged = false;
    Player *owner = nullptr;

public:

    Residence(std::string name, int purchase_cost, std::vector<int> rentMoney);
    

    int getCost() const;
    int getUpgradeLevel() const;
    std::string getName() const;
    bool isBought() const;
    virtual bool isMortgaged() const override;
    int getRent() const;
    virtual Player *getOwner() const override;

    void upgrade(); // upgrading property
    void mortgage(); // mortgage
    void buy(Player *p); // buying
    void payRent(Player *payer);

    virtual void setOwner(Player *p) override;
    void setMortgaged();
    // to whoever does board, we are doing a map where each index will map to the tile we are on and its block type
};

#endif
