#include <string>
#include <vector>
#include "player.h"
#include <bits/stdc++.h> 


using namespace std;

Player::Player(string name, char chr, int liquidCash, int mortageValue, int totalAssetsValue, int playerPosition) :
  name{name},
  chr{chr},
  liquidCash{liquidCash},
  mortageValue{mortageValue},
  totalAssetsValue{totalAssetsValue},
  playerPosition{playerPosition} {}



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
  if (liquidCash + mortageValue >= propertyPrice){
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

void Player::addProperty(Square * s){
  ownedProperties.push_back(s);
}

  //Getters
string Player::getPlayerName() const{
  return name;
}

int Player::getLiquidCash() const {
  return liquidCash;
}

int Player::getMortageValue() const {
  return mortageValue;
}

int Player::getTotalAssetsValue() const {
  return totalAssetsValue;
}

int Player::getPlayerPostion() const {
  return playerPosition;
}

const vector<Square*>& Player::getPlayerProperties() const {
  return ownedProperties;
}

//Setters
void Player::setPlayerName(string name){
  this->name = name;
}

void Player::setLiquidCash(int liquidCash){
  this->liquidCash = liquidCash;
}

void Player::setMortageValue(int mortageValue){
  this->mortageValue = mortageValue;
}

void Player::setTotalAssetsValue(int totalAssetsValue){
  this->totalAssetsValue = totalAssetsValue;
}

void Player::setPlayerPostion(int playerPosition){
  this->playerPosition = playerPosition;
}

void Player::setSymbol(char symbol) {chr = symbol; }
