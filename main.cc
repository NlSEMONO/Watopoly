#include "board.h"
#include "academic.h"
#include "square.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
using namespace std;

int main(int argc, char** argv) {
    bool testing = false;
    string file = "";
    Board b;

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (argv[i] == "-testing") testing = true;
            else if (argv[i] == "-load") {
                if (i + 1 >= argc) {
                    cerr << "Please specify a file name" << endl;
                    return 1;
                }
                file = argv[i + 1];
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
    cout << "Enter # of players: " << endl;
    while (!(in >> numPlayers)) {
        cout << "Invalid # of players, please try again." << endl;
        in.clear();
        in.ignore();
    }

    // load state
    string line;
    if (file != "") {
        while (getline(in, line)) {
            istringstream iss{line};
            string cmd;
            iss >> cmd;
            
        }
    }
}
