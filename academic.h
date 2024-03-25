#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__
#include <vector>
#include <string>
#include "player.h"

class Academic {
    std::string monopoly_block;
    std::string name;
    int purchase_cost;
    int upgrade_cost;
    int upgrade_level;
    std::vector<int> rentMoney;
    bool bought;
    bool mortgaged;

    public:

    Academic(std::string monopoly_block, std::string name, int purchase_cost, 
             int upgrade_cost, int upgrade_level, std::vector<int> rentMoney);
    

    std::string getBlock();
    std::string getName();
    void upgrade(Player *p);

    void mortgage(Player *p);
    void buy(Player *p);

    // to whoever does board, we are doing a map where each index will map to the tile we are on and its block type
};

#endif
