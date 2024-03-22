#ifndef __PROPERTY_H__
#define __PROPERTY_H__
#include <vector>
#include <string>

class Property {
    bool bought;
    bool mortgaged;
    int price;
    int upgrades;
    std::string name;
    std::vector<int> rentMoney;
    
};

#endif
