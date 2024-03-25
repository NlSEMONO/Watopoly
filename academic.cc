#include <vector>
#include <string>
#include "player.h"
#include "academic.h"
using namespace std;


Academic::Academic(string monopoly_block, string name, int purchase_cost, 
             int upgrade_cost, int upgrade_level, vector<int> rentMoney): 
             monopoly_block{monopoly_block}, name{name}, purchase_cost{purchase_cost}, upgrade_cost{upgrade_cost},
             upgrade_level{upgrade_level}, rentMoney{rentMoney}, bought{false}, mortgaged{false} {}


// getters
string Academic::getBlock() const {return monopoly_block;}
string Academic::getName() const {return name;}
int Academic::getCost() const {return purchase_cost;}
int Academic::getUpgrade_cost() const {return upgrade_cost;}
int Academic::getUpgradeLevel() const {return upgrade_level;}
bool Academic::isBought() const {return bought;}
bool Academic::isMortgaged() const {return mortgaged;}
int Academic::getRent() const {return rentMoney[upgrade_level];}
Player *Academic::getOwner() const {return owner;}

// upgradeProperty
void Academic::upgrade() {
    owner->changeCash(upgrade_cost, false);
    upgrade_level++;    
} 

// mortgageProperty
void Academic::mortgage() {
    owner->changeCash(purchase_cost / 2, true);
    mortgaged = true;
}

//buyProperty
void Academic::buy(Player *p) {
    p->changeCash(purchase_cost, false); 
    p->addProperty(this);
    owner = p;
    bought = true;
}

// payRent
void Academic::payRent(Player *payer) {
    owner->changeCash(getRent(), true);
    payer->changeCash(getRent(), false);
}
