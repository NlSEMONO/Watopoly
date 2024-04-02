#include <vector>
#include <string>
#include "player.h"
#include "residence.h"
using namespace std;


Residence::Residence(string name, int purchase_cost, std::vector<int> rentMoney) : Square{name}, purchase_cost{purchase_cost}, rentMoney{rentMoney} {}
    

string Residence::getName() const {return name;}
int Residence::getCost() const {return purchase_cost;}
bool Residence::isBought() const {return bought;}
bool Residence::isMortgaged() const {return mortgaged;}
int Residence::getRent(int residencesOwned) const {return rentMoney[residencesOwned];}
Player *Residence::getOwner() const {return owner;}

void Residence::upgrade(){
    owner->changeCash(purchase_cost, false);
}

void Residence::mortgage(int amountBack){
    owner->changeCash(amountBack, false);
    mortgaged = true;  
}

void Residence::buy(Player *p){
    p->changeCash(purchase_cost, false); 
    // p->addProperty(this);
    owner = p;
    bought = true;   
}

void Residence::payRent(Player *payer, int residencesOwned){
    owner->changeCash(getRent(residencesOwned), true);
    payer->changeCash(getRent(residencesOwned), false);
}

void Residence::setOwner(Player* p) {owner = p; }

void Residence::setMortgage(bool mortgage) {mortgaged = mortgage; }

int Residence::getMortgageCost() const {return purchase_cost/2;}
