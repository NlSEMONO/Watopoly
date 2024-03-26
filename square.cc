#include "square.h"

Square::Square(): players{} {}

void Square::addPlayer(Player* player) {
    players.push_back(player);
}

void Square::removePlayer(Player* player) {
    for (auto it = players.begin(); it != players.end();) {
        if (*it == player) it = players.erase(it);
        else ++it;
    }
}
