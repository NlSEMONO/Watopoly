#include <string>
#include <vector>
#include "player.h"


Player::Player(string name, int liquidCash, int mortageValue, int totalAssetsValue, int playerPosition) :
  name{name},
  liquidCash{liquidCash},
  mortageValue{mortageValue},
  totalAssetsValue{totalAssetsValue},
  playerPosition{playerPosition},
  ownedProperties{ownedProperties} {}



int Player::movePlayer(int diceRoll){
  if (playerPosition + diceRoll <= 40){
    playerPosition += diceRoll;
    return playerPosition;
  } else {
    playerPosition += diceRoll;
    playerPosition -= 40;
    return playerPosition;
  }
}


bool Player::canAfford(int propertyPrice){
  if (liquidCash >= propertyPrice){
    return true;
  } else if ( liquidCash + mortageValue >= propertyPrice){
    return true;
  } else {
    return false;
  }
}

void Player::changeCash(int value, bool increase){
  if (increase){
    liquidCash += value;
  } else {
    liquidCash -= value;
  }
}
