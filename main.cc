#include "board.h"
#include "academic.h"
#include "square.h"
#include "game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
using namespace std;

int main(int argc, char** argv) {
    bool testing = false;
    string file = "";
    Game game;

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            istringstream iss{argv[i]};
            string str;
            iss >> str;
            // cout << str << endl;
            if (str == "-testing") testing = true;
            else if (str == "-load") {
                if (i + 1 >= argc) {
                    cerr << "Please specify a file name" << endl;
                    return 1;
                }
                // cout << "lol" << endl;
                // cout << argv[i + 1] << endl;
                file = argv[i + 1];
                // cout << argv[i] << endl;
                ++i;
            }
        }
    }
    istream* input = &cin; 
    ifstream iss;
    if (file != "") {
        iss = ifstream{file};
        if (iss.fail()) {
            cerr << "Please make sure the file is in the same directory as this file." << endl;
            return 2;
        }
        input = &iss;
    }
    // get # of players
    istream& in = *input;
    int numPlayers = -1;
    cout << "How many players will be playing the game?" << endl;
    string s;
    while (getline(in, s)){
        istringstream iss{s};
        // cout << s << endl;
        if (iss >> numPlayers){
            if ((1 <= numPlayers) && (numPlayers <= 8)){
                break;
            }
        }
        throw runtime_error{"Please enter a valid number between 1 and 8"};
    }

    // load state
    // string line;
    game.setPlayers(numPlayers);
    // cout << file << endl;
    if (file != "") {
        try {
            game.loadFile(in);
        }
        catch (std::bad_cast&) {
            cerr << "Building that cannot be owned was inputted. Please try again." << endl;
            return 3;
        }
        catch (std::exception& e) {
            cerr << e.what() << endl;
            return 4;
        }
    } else {
        try {
            game.initPlayers();
        }
        catch (std::exception& e) {
            cerr << e.what() << endl;
            return 5;
        }
    }
    cout << game;
    game.play();
}
