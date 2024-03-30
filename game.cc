#include <sstream>
#include "game.h"
#include "slcrng.h"
#include "needlesrng.h"
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
        
        iss >> name;
        iss >> chr;
        iss >> cups;
        iss >> money;
        iss >> position;
        if (position == 10) {
            int mode, turns;
            iss >> mode;
            if (mode == 0) {
                
            }
        } else {

        }
    }

    // load buildings
}

void Game::play() {

}