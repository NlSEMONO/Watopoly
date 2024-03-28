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
int Gym::getGymsOwned() const {return gymsOwned;}
bool Gym::isBought() const {return bought;}
bool Gym::isMortgaged() const {return mortgaged;}


void Gym::upgrade() {
    gymsOwned++;    
} 

// mortgageProperty
void Gym::mortgage() {
    owner->changeCash(purchase_cost / 2, true);
    mortgaged = true;
}

void Gym::unmortgage() {
    mortgaged = false;
    owner->changeCash((purchase_cost * 6) / 10, true);
}

//buyProperty
void Gym::buy(Player *p) {
    gymsOwned = 1;
    p->changeCash(purchase_cost, false); 
    p->addProperty(this);
    owner = p;
    bought = true;
}

// payRent
void Gym::payRent(Player *payer, int diceRoll) const {
    if (gymsOwned == 1) {
        owner->changeCash(4 * diceRoll, true);
        payer->changeCash(4 * diceRoll, false);
    } else {
        owner->changeCash(10 * diceRoll, true);
        payer->changeCash(10 * diceRoll, false);
    }
}
