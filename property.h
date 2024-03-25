#ifndef __PROPERTY_H__
#define __PROPERTY_H__
#include <vector>
#include <string>
#include "player.h"

class Property {
    bool bought;
    bool mortgaged;
    int price;
    int upgrades;
    std::string name;
    std::vector<int> rentMoney;
    
    bool canBuy(Player p);
    void buy(Player p);
};

#endif
