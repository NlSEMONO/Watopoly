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
    
    virtual int getCost() const override;
    int getUpgrade_cost() const;
    int getUpgradeLevel() const;
    std::string getBlock() const;
    virtual std::string getName() const;
    bool isBought() const;
    virtual bool isMortgaged() const override;
    int getRent(bool monopoly) const;
    virtual Player *getOwner() const override;

    void upgrade(); // upgrading property
    void sellUpgrade();
    virtual void mortgage(int amountBack) override; // mortgage
    virtual void unmortgage() override;
    virtual void buy(Player *p) override; // buying
    void payRent(Player *payer, bool monopoly_owned);
    virtual ~Academic();

    virtual void setOwner(Player *p) override;
    void setUpgrades(int u);
    virtual void setMortgage(bool mortgage) override;
    std::string printImprovements() const;
    virtual int getMortgageCost() const override;

    // to whoever does board, we are doing a map where each index will map to the tile we are on and its block type
};

#endif
