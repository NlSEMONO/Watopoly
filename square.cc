#include "square.h"
#include <iostream>
using namespace std;

Square::Square(std::string name): name{name}, players{} {}

Square::~Square() {
    cout << "ASDJKLASD" << endl;
};

std::string Square::getName() const {
    return name;
}

void Square::addPlayer(Player* player) {
    players.push_back(player);
}

void Square::removePlayer(Player* player) {
    for (auto it = players.begin(); it != players.end();) {
        if (*it == player) it = players.erase(it);
        else ++it;
    }
}
