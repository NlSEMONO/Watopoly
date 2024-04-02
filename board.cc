#include "board.h"
#include "academic.h"
#include "residence.h"
#include "dice.h"
#include "osap.h"
#include "slc.h"
#include "needleshall.h"
#include "tuition.h"
#include "jail.h"
#include "gym.h"
#include "coop.h"
#include "goosenest.h"
#include "gototims.h"
#include <iostream>
#include <string>

using namespace std;

Board::Board(): squares{}, nameToIndex{}, monopolies{} {
    const vector<int> residenceRents{25, 50, 100, 200};
    const int gymCost = 150;
    const int residenceCost = 200;
    // hardcoding all buildings

    squares.push_back(std::unique_ptr<OSAP>{new OSAP{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts1", "AL", 40, 50, 0, {2, 10, 30, 90, 160, 250}}});
    squares.push_back(std::unique_ptr<SLC>{new SLC{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts1", "ML", 60, 50, 0, {4, 20, 60, 180, 320, 450}}});
    squares.push_back(std::unique_ptr<Tuition>{new Tuition{}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"MKV", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "ECH", 100, 50, 0, {6, 30, 90, 270, 400, 550}}});
    squares.push_back(std::unique_ptr<NeedlesHall>{new NeedlesHall{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "PAS", 100, 50, 0, {6, 30, 90, 270, 400, 550}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "HH", 120, 50, 0, {8, 40, 100, 300, 450, 600}}});
    squares.push_back(std::unique_ptr<Jail>{new Jail{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "RCH", 140, 100, 0, {10, 50, 150, 450, 625, 750}}});
    squares.push_back(std::unique_ptr<Gym>{new Gym{"PAC", gymCost}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "DWE", 140, 100, 0, {10, 50, 150, 450, 625, 750}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "CPH", 160, 100, 0, {12, 60, 180, 500, 700, 900}}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"UWP", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "LHI", 180, 100, 0, {14, 70, 200, 550, 750, 950}}});
    squares.push_back(std::unique_ptr<SLC>{new SLC{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "BMH", 180, 100, 0, {14, 70, 200, 550, 750, 950}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "OPT", 200, 100, 0, {16, 80, 220, 600, 800, 1000}}});
    squares.push_back(std::unique_ptr<GooseNest>{new GooseNest{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV1", 220, 150, 0, {18, 90, 250, 700, 875, 1050}}});
    squares.push_back(std::unique_ptr<NeedlesHall>{new NeedlesHall{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV2", 220, 150, 0, {18, 90, 250, 700, 875, 1050}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV3", 240, 150, 0, {20, 100, 300, 750, 925, 1100}}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"V1", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "PHYS", 260, 150, 0, {22, 110, 330, 800, 975, 1150}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "B1", 260, 150, 0, {22, 110, 330, 800, 975, 1150}}});
    squares.push_back(std::unique_ptr<Gym>{new Gym{"CIF", gymCost}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "B2", 280, 150, 0, {24, 120, 360, 850, 1025, 1200}}});
    squares.push_back(std::unique_ptr<GoToTims>{new GoToTims{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "EIT", 300, 200, 0, {26, 130, 390, 900, 1100, 1275}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "ESC", 300, 200, 0, {26, 130, 390, 900, 1100, 1275}}});
    squares.push_back(std::unique_ptr<SLC>{new SLC{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "C2", 320, 200, 0, {28, 150, 450, 1000, 1200, 1400}}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"REV", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<NeedlesHall>{new NeedlesHall{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Math", "MC", 350, 200, 0, {35, 175, 500, 1100, 1300, 1500}}});
    squares.push_back(std::unique_ptr<Coop>{new Coop{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Math", "DC", 400, 200, 0, {50, 200, 600, 1400, 1700, 2000}}});

    // store names to relevant index in a map (so we don't have to loop during game execution)
    int count = 0;
    for (auto& it : squares) {
        nameToIndex[it.get()->getName()] = count;
        ++count;
    }

    // map monopoly names to relevant properties
    monopolies["Arts1"] = {1, 3}; 
    monopolies["Arts2"] = {6, 8, 9};
    monopolies["Eng"] = {11, 13, 14};
    monopolies["Health"] = {16, 18, 19};
    monopolies["Env"] = {21, 23, 24};
    monopolies["Sci1"] = {26, 28, 29};
    monopolies["Sci2"] = {31, 32, 34};
    monopolies["Math"] = {37, 39};
    monopolies["Residence"] = {5, 15, 25, 35};
    monopolies["Gyms"] = {12, 28};
    monopolies["SLC"] = {2, 17, 33};
    monopolies["Needles"] = {7, 22, 36};
}

// int Board::rollDice(){
//     Dice Dice1;
//     Dice Dice2;
//     Event e1 = Dice1.generateEvent();
//     Event e2 = Dice2.generateEvent();
//     int roll1 = Dice1.eventToInt(e1);
//     int roll2 = Dice1.eventToInt(e2);
//     return roll1 + roll2;
// }

// void Board::makeMove(Player *p) {
//     int diceRoll = rollDice();
//     p->movePlayer(diceRoll);
// }

// void Board::addPlayer(std::string name) {
//     players.push_back(std::unique_ptr<Player>{new Player{name, 0, 0, 0, 0}});
//     currentPlayer++;
// }

bool Board::isType(string type, int buildingCode) {
    if (monopolies.count(type) == 0) return false;
    vector<int>& toSearch = monopolies[type];

    return find(toSearch.begin(), toSearch.end(), buildingCode) != toSearch.end();
}

bool Board::isGym(int buildingCode) { return isType("Gyms", buildingCode); }

bool Board::isResidence(int buildingCode) { return isType("Residence", buildingCode); }

bool Board::isAcademic(int buildingCode) {
    return isType("Arts1", buildingCode) || isType("Arts2", buildingCode) || isType("Eng", buildingCode) || 
            isType("Health", buildingCode) || isType("Env", buildingCode) || isType("Sci1", buildingCode) || 
            isType("Sci2", buildingCode) || isType("Math", buildingCode);
}

bool Board::isOwnable(int buildingCode) {return isAcademic(buildingCode) || isType("Gyms", buildingCode) || isType("Residence", buildingCode); } 

void Board::initBuilding(std::string name, Player* owner, int upgrades) {
    if (nameToIndex.count(name) == 0) return;
    int buildingCode = nameToIndex[name];

    if (isType("Residence", buildingCode)) {
        Residence& toChange = dynamic_cast<Residence&>(*squares[buildingCode].get());
        toChange.setOwner(owner);
        if (upgrades == -1) toChange.setMortgage();
    } else if (isType("Gyms", buildingCode)) {
        Gym& toChange = dynamic_cast<Gym&>(*squares[buildingCode].get());
        toChange.setOwner(owner);
        if (upgrades == -1) toChange.setMortgage();
    } else if (isAcademic(buildingCode)) {
        Academic& toChange = dynamic_cast<Academic&>(*squares[buildingCode].get());
        toChange.setOwner(owner);
        if (upgrades > -1) toChange.setUpgrades(upgrades);
        else toChange.setMortgage();
    }
}

Square *Board::getSquare(string name) {return squares[nameToIndex[name]].get();}
Square *Board::getSquare(int buildingCode) {return squares[buildingCode].get(); } 
int Board::getIndex(string name) { return nameToIndex[name];}
bool Board::ownsAll(Player* p, int position) {
    Academic* building = dynamic_cast<Academic*>(squares[position].get());
    vector<int> toCheck = monopolies[building->getBlock()];
    for (size_t i = 0; i < toCheck.size(); ++i) if (squares[toCheck[i]]->getOwner() != p) return false;
    return true;
}

void Board::getOwnedSquares(Player* owner, vector<Square *>& dest) const {
    for (size_t i = 0; i < squares.size(); ++i) if (squares[i].get()->getOwner() == owner) dest.push_back(squares[i].get());
}

void Board::saveProperties(ostream& out) {
    for (size_t i = 0; i < squares.size(); ++i) {
        if (isOwnable(i)) {
            Square* curr = squares[i].get();
            out << curr->getName() << " " << (curr->getOwner() == nullptr ? "BANK" : curr->getOwner()->getPlayerName()) << " ";
            if (curr->isMortgaged()) out << -1 << endl;
            else if (isGym(i) || isResidence(i)) out << 0 << endl;
            else {
                Academic* temp = dynamic_cast<Academic*>(curr);
                out << temp->getUpgradeLevel() << endl;
            }
        }
    }
}
