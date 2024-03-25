#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include "square.h"

class Player {
  std::string name;
  int liquidCash;
  int mortageValue;
  int totalAssetsValue;
  int playerPosition;
  std::vector<Square*> ownedProperties;

public:
  Player(std::string name, int liquidCash, int mortageValue, int totalAssetsValue, int playerPosition);
  int movePlayer(int diceRoll);
  bool canAfford(int propertyPrice);
  void changeCash(int value, bool increase);
  void addProperty(Square * s);

  //Getters
  std::string getPlayerName() const;
  int getLiquidCash() const;
  int getMortageValue() const;
  int getTotalAssetsValue() const;
  int getPlayerPostion() const;

  //Setters
  void setPlayerName(std::string setName);
  void setLiquidCash(int liquidCash);
  void setMortageValue(int mortageValue);
  void setTotalAssetsValue(int totalAssetsValue);
  void setPlayerPostion(int position);


};

#endif
