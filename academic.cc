#include <vector>
#include <string>
#include "player.h"
#include "academic.h"
#include <iostream>
using namespace std;

Academic::~Academic() {}

Academic::Academic(string monopoly_block, string name, int purchase_cost, 
             int upgrade_cost, int upgrade_level, vector<int> rentMoney): 
             Square{name}, monopoly_block{monopoly_block}, purchase_cost{purchase_cost}, 
             upgrade_cost{upgrade_cost},upgrade_level{upgrade_level}, rentMoney{rentMoney} {}


// getters
string Academic::getBlock() const {return monopoly_block;}
string Academic::getName() const {return name;}
int Academic::getCost() const {return purchase_cost;}
int Academic::getUpgrade_cost() const {return upgrade_cost;}
int Academic::getUpgradeLevel() const {return upgrade_level;}
bool Academic::isBought() const {return bought;}
bool Academic::isMortgaged() const {return mortgaged;}
int Academic::getRent(bool monopoly) const {return (monopoly && upgrade_level == 0) ? rentMoney[0] * 2 :  rentMoney[upgrade_level];}
Player *Academic::getOwner() const {return owner;}

// upgradeProperty
void Academic::upgrade() {
    owner->changeCash(upgrade_cost, false);
    upgrade_level++;    
} 

void Academic::sellUpgrade() {
    owner->changeCash(upgrade_cost / 2);
    --upgrade_level;
}

// mortgageProperty
void Academic::mortgage(int amountBack) {
    owner->changeCash(amountBack, true);
    upgrade_level = 0;
    mortgaged = true;
}

void Academic::unmortgage() {
    mortgaged = false;
    owner->changeCash((purchase_cost * 6) / 10, false);
}

//buyProperty
void Academic::buy(Player *p) {
    p->changeCash(purchase_cost, false); 
    // p->addProperty(this);
    owner = p;
    bought = true;
}

// payRent
void Academic::payRent(Player *payer, bool monopoly_Owned) {
    owner->changeCash(getRent(monopoly_Owned), true);
    payer->changeCash(getRent(monopoly_Owned), false);
    // if (!monopoly_Owned) {
    //     owner->changeCash(getRent(monopoly_Owned), true);
    //     payer->changeCash(getRent(monopoly_Owned), false);
    // } else if (monopoly_Owned && (upgrade_level == 0)) {
    //     owner->changeCash(getRent(monopoly_Owned), true);
    //     payer->changeCash(getRent() * 2, false);
    // } else {
    //     owner->changeCash(getRent(), true);
    //     payer->changeCash(getRent(), false);
    // }
}

string Academic::printImprovements() const {
    string tmp = "";
    tmp += string(upgrade_level, 'I');
    tmp += string(7 - upgrade_level, ' ');
    tmp += "|";
    return tmp;
}

void Academic::setOwner(Player* p) {owner = p; } 

void Academic::setUpgrades(int u) { upgrade_level = u; }

void Academic::setMortgage(bool mortgage) {mortgaged = mortgage; }

int Academic::getMortgageCost() const {return purchase_cost/2 + ((upgrade_level * upgrade_cost) / 2);}
