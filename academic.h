#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__
#include <vector>
#include <string>
#include "player.h"
#include "square.h"

class Academic: public Square {
    std::string monopoly_block;
    Player *owner = nullptr;
    int purchase_cost;
    int upgrade_cost;
    int upgrade_level;
    std::vector<int> rentMoney;
    bool bought = false;
    bool mortgaged = false;

    public:

    Academic(std::string monopoly_block, std::string name, int purchase_cost, 
             int upgrade_cost, int upgrade_level, std::vector<int> rentMoney);
    
    int getCost() const;
    int getUpgrade_cost() const;
    int getUpgradeLevel() const;
    std::string getBlock() const;
    std::string getName() const;
    bool isBought() const;
    bool isMortgaged() const;
    int getRent() const;
    Player *getOwner() const;

    void upgrade(); // upgrading property
    void mortgage(); // mortgage
    void unmortgage();
    void buy(Player *p); // buying
    void payRent(Player *payer);
    virtual ~Academic();

    void setOwner(Player *p);
    void setUpgrades(int u);

    // to whoever does board, we are doing a map where each index will map to the tile we are on and its block type
};

#endif
