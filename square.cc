#include "square.h"
using namespace std;

Square::Square(std::string name): name{name}, players{} {}

Square::~Square() {};

std::string Square::getName() const { return name; }

void Square::addPlayer(Player* player) { players.push_back(player); }

void Square::removePlayer(Player* player) {
    for (auto it = players.begin(); it != players.end();) {
        if (*it == player) it = players.erase(it);
        else ++it;
    }
}

Player* Square::getOwner() const { return nullptr; }

string Square::printPlayers() {
    string tmp; 
    for (size_t i = 0; i < players.size(); ++i) {
        tmp += players[i]->getSymbol();
    }

    for (size_t j = 0; j < 7-players.size(); ++j) {
        tmp += " ";
    }
    return tmp + "|";
}

void Square::setOwner(Player *player) {
// do nothing    
}

bool Square::isMortgaged() const {
    return false;
}

void Square::buy(Player* p) {}

void Square::mortgage(int amountBack) {}

void Square::unmortgage() {}

int Square::getMortgageCost() const{return 0;}

// string Square::getBlock() const { return ""; }

int Square::getCost() const { return 0; }

void Square::setMortgage(bool mortgage) {};
