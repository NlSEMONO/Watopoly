#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include "square.h"

class Square;

class Player {
  std::string name;
  char symbol;
  int liquidCash;
  int mortageValue;
  int totalAssetsValue;
  int playerPosition;

public:
  Player(std::string name, char chr, int liquidCash, int mortageValue, int totalAssetsValue, int playerPosition);
  int movePlayer(int diceRoll);
  bool canAfford(int propertyPrice);
  void changeCash(int value, bool increase = true);
  // void addProperty(Square * s);

  //Getters
  std::string getPlayerName() const;
  int getLiquidCash() const;
  int getMortageValue() const;
  int getTotalAssetsValue() const;
  int getPlayerPostion() const;
  const std::vector<Square*> &getPlayerProperties() const;
  char getSymbol() const;

  //Setters
  void setPlayerName(std::string name);
  void setLiquidCash(int liquidCash);
  void setMortageValue(int mortageValue);
  void setTotalAssetsValue(int totalAssetsValue);
  void setPlayerPostion(int playerPosition);
  void setSymbol(char symbol);
};

#endif
