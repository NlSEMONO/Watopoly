#include <string>
#include <vector>
#include "player.h"


Player::Player(string name, int liquidCash, int assetsValue, int playerPosition) :
  name{name},
  liquidCash{liquidCash},
  assetsValue{assetsValue},
  playerPosition{playerPosition} {}


int Player::movePlayer(int diceRoll){
  playerPosition += diceRoll;
  return playerPosition;
}


bool Player::canAfford(int propertyPrice){
  assetsValue
  if (liquidCash >= propertyPrice){
    return true;
  } else if ()
}
