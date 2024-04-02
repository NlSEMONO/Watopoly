#include <vector>
#include <string>
#include "player.h"
#include "square.h"
#include "gym.h"

using namespace std;

Gym::Gym(std::string name, int purchase_cost): Square{name}, purchase_cost{purchase_cost} {}


// getters
string Gym::getName() const {return name;}
Player *Gym::getOwner() const {return owner;}
int Gym::getCost() const {return purchase_cost;}
bool Gym::isBought() const {return bought;}
bool Gym::isMortgaged() const {return mortgaged;}
int Gym::getRent(int gymsOwned, int diceRoll) const {
    if (gymsOwned == 2) {
        return diceRoll * 10;
    } else {
        return diceRoll * 4;
    }
}


// mortgageProperty
void Gym::mortgage(int amountBack) {
    owner->changeCash(amountBack, true);
    mortgaged = true;
}

void Gym::unmortgage() {
    mortgaged = false;
    owner->changeCash((purchase_cost * 6) / 10, true);
}

//buyProperty
void Gym::buy(Player *p) {
    p->changeCash(purchase_cost, false); 
    // p->addProperty(this);
    owner = p;
    bought = true;
}

// payRent
void Gym::payRent(Player *payer, int gymsOwned, int diceRoll) const {
    owner->changeCash(getRent(gymsOwned, diceRoll), true);
    payer->changeCash(getRent(gymsOwned, diceRoll), false);
}

void Gym::setOwner(Player* p) {owner = p; }

void Gym::setMortgage(bool mortgage) {mortgaged = mortgage; }
