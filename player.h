#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include "property.h"

class Player {
  std::string name;
  int liquidCash;
  int mortageValue;
  int playerPosition;
  std::vector<Property> ownedProperties;
public:
  Player(std::string name, int liquidCash, int assetsValue, int playerPosition);
  int movePlayer(int diceRoll);
  bool canAfford(int propertyPrice);
  void reduceAssets(int value);
};

#endif
