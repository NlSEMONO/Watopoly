#include <vector>
#include <string>
#include "player.h"
#include "residence.h"
using namespace std;


Residence::Residence(string name, int purchase_cost, std::vector<int> rentMoney) : name{name}, purchase_cost{purchase_cost}, rentMoney{rentMoney} {}
    

string Residence::getName() const {return name;}
int Residence::getCost() const {return purchase_cost;}
int Residence::getUpgradeLevel() const {return residences_owned;}
bool Residence::isBought() const {return bought;}
bool Residence::isMortgaged() const {return mortgaged;}
int Residence::getRent() const {return rentMoney[residences_owned];}
Player *Residence::getOwner() const {return owner;}

void Residence::upgrade(){
    owner->changeCash(purchase_cost, false);
    residences_owned++;
}

void Residence::mortgage(){
    owner->changeCash(purchase_cost / 2, true);
    mortgaged = true;  
}

void Residence::buy(Player *p){
    p->changeCash(purchase_cost, false); 
    p->addProperty(this);
    owner = p;
    bought = true;   
}

void Residence::payRent(Player *payer){
    owner->changeCash(getRent(), true);
    payer->changeCash(getRent(), false);
}
