#include <sstream>
#include "game.h"
#include "slcrng.h"
#include "needlesrng.h"
#include <stdexcept>
using namespace std;

void Game::setPlayers(int pCount) { playerCount = pCount; }

void Game::loadFile(istream& in) {
    string line;

    // load players 
    for (int i = 0; i < playerCount; ++i) {
        getline(in, line);
        istringstream iss{line};
        string name = "";
        char chr = '/';
        int cups = -100, money = -10000, position = -40;
        
        if (!(iss >> name)) throw runtime_error{"Could not read name."};
        if (!(iss >> chr)) throw runtime_error{"Could not read character."};
        if (!(iss >> cups)) throw runtime_error{"Could not read cups."};
        if (!(iss >> money)) throw runtime_error{"Could not read money."};
        if (!(iss >> position)) throw runtime_error{"Could not read position."};
        if (position == 10) {
            int mode, turns;
            if (!(iss >> mode)) throw runtime_error{"Please provide whether jailed/not jailed."};
            // add player data into players
            players.push_back(unique_ptr<Player>(new Player{name, chr, money, 0, 0, position}));
            numCups[players[i].get()] = cups;
            if (mode == 1) {
                if (!(iss >> turns)) throw runtime_error{"Please specify # of turns in jail."};
                jailedTurns[players[i].get()] = turns;
            }
        } else {
            players.push_back(unique_ptr<Player>(new Player{name, chr, money, 0, 0, position}));
            numCups[players[i].get()] = cups;
        }
        nameToPlayer[name] = players[i].get();
        cupsDistributed += cups;
    }

    // load buildings
    const int BUILDING_COUNT = 40;
    while (getline(in, line)) {
        istringstream iss{line};
        string building, owner;
        int upgs;
        if (!(iss >> building)) throw runtime_error{"Could not read building."};
        if (!(iss >> owner)) throw runtime_error{"Could not read owner."};
        if (!(iss >> upgs)) throw runtime_error{"Could not read # of upgrades."};
        b.initBuilding(building, owner == "BANK" ? nullptr : nameToPlayer[owner], upgs);
    }
}

void Game::play() {

}
