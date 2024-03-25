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
string Academic::getBlock() {return monopoly_block;}
string Academic::getName() {return name;}
int Academic::getCost() {return purchase_cost;}
int Academic::getUpgrade_cost() {return upgrade_cost;}
int Academic::getUpgradeLevel() {return upgrade_level;}
bool Academic::isBought() {return bought;}
bool Academic::isMortgaged() {return mortgaged;}


void Academic::upgrade(Player *p) {
    p->changeCash(upgrade_cost, false);
    upgrade_level++;    
} 

void Academic::mortgage(Player *p) {
    p->changeCash(purchase_cost / 2, true);
    mortgaged = true;
}

void Academic::buy(Player *p) {
    p->changeCash(purchase_cost, false); 
    p->addProperty(this);
    bought = true;
}
