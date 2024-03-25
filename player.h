#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include "property.h"

class Player {
  string name;
  int liquidCash;
  int mortageValue;
  int playerPosition;
  std::vector<property> ownedProperties;
public:
  Player(string name, int liquidCash, int assetsValue, int playerPosition);
  int movePlayer(int diceRoll);
  bool canAfford(int propertyPrice);
};

#endif
