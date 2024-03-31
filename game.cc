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
    cout << "How many players will be playing the game?" << endl;
    string s;
    int numPlayers;
    while (cin >> s){
        istringstream iss{s};
        if (iss >> numPlayers){
            if ((1 <= numPlayers) && (numPlayers <= 8)){
                break;
            }
        }
        throw runtime_error{"Please enter a valid number between 1 and 8"};
    }

    //Player Name Init
    string nameOfPLayer;
    int i = 0;
    vector<char> possibleSymbols = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
    vector<string> names = {};
    int cnt = 0;
    while(i < numPlayers){
        cout << "Name of player " << i << ":" << endl;
        cnt = count(names.begin(), names.end(), nameOfPLayer);
        if ((cin >> nameOfPLayer) && (cnt == 0)){
          players[i] = unique_ptr<Player>{new Player{nameOfPLayer, '\0', 1500, 0, 0, 0}};
          i++;
          names.push_back(nameOfPLayer);
        } else {
            throw runtime_error{"Please enter a valid name that has not been selected"};
        }
    }

    //Player Symbol Init
    int j = 0;
    string s1;
    char playerSymbol;
    int cnt1 = 0;
    while(j < numPlayers){
        cout << "Symbol of player " << j << ":" << endl;
        cin >> s1;
        istringstream iss{s1};
        if (iss >> playerSymbol){
            cnt1 = count(possibleSymbols.begin(), possibleSymbols.end(), playerSymbol);
            if (((playerSymbol == 'G') || (playerSymbol == 'B') || (playerSymbol == 'D') ||(playerSymbol == 'P') || (playerSymbol == 'S') ||
                (playerSymbol == '$') || (playerSymbol == 'L') || (playerSymbol == 'T')) && (cnt1 == 1)) {
                    players[j]->setSymbol(playerSymbol);
                    for (int i = 0; i < possibleSymbols.size(); i++){
                        if (possibleSymbols[i] == playerSymbol){
                            possibleSymbols.erase(possibleSymbols.begin() + i);
                            break;
                        }
                    }
                    i++;
                    continue;
                } else {
                    throw runtime_error{"Please enter a valid symbol that has not been selected"};
                    continue;
                }
        } else {
            throw runtime_error{"Please enter a valid symbol that has not been selected"};
            continue;
        }
    }

    cout << "Game has been intialized with " << numPlayers << "!" << endl;

    //CLI Interpreter
    string cmdWhole;
    int playerTurn = 0;

    while(getline(cin, cmdWhole)){
        istringstream iss2{cmdWhole};
        string cmd;
        iss2 >> cmd;

        if (cmd == "roll"){
            // b.makeMove(players[playerTurn].get());  
        } else if (cmd == "next"){

        } else if (cmd == "trade"){
            string param1;
            string param2;
            iss2 >> param1;
            iss2 >> param2;
            
        } else if (cmd == "improve"){
            
        } else if (cmd == "mortgage"){
            
        } else if (cmd == "unmortgage"){
            
        } else if (cmd == "bankrupt"){
            
        } else if (cmd == "assets"){
            
        } else if (cmd == "all"){
            
        } else if (cmd == "save"){
            
        } else {
            throw runtime_error{"Not a valid command"};
        }

        playerTurn++;
        if (playerTurn == numPlayers){
            playerTurn = 0;
        }
    }
}

const int sqr_len = 7;
const int board_len = 11;

const char divider = '|';
const string academic_border = string("-",sqr_len) + divider;
const string empty_block = string(" ", sqr_len) + divider;
const string block_bottom = string("_",sqr_len) + divider;
const string three_empty = string(" ", 3) + divider;
const string four_empty = string(" ", 4) + divider;
const string five_empty = string(" ", 5) + divider;
const string empty_middle_section = string(" ", (8 * 9) - 1) + divider;
const string blank_middle_section = divider + empty_block + empty_middle_section + empty_block;
const string middle_block_bottom = divider + block_bottom + empty_middle_section + block_bottom;
const string middle_academic_border = divider + academic_border + empty_middle_section + academic_border;
const string wat_surround = string(" ", 12) + divider;

ostream &operator<<(ostream &out, Board &board) {
    out << string("_" , 8 * 11) << endl; // top border

    // first row of blocks 
    // printing the first row of board
    out << "|Goose  |" << empty_block << "|NEEDLES|" << empty_block;
    out << empty_block << "V1" << five_empty << empty_block;
    out << empty_block << "CIF" << four_empty << empty_block;
    out << "GO TO  |" << endl;

    // printing the second row of board
    out << divider << "Nesting" << divider << academic_border << "HALL" << three_empty;
    out << academic_border << academic_border << empty_block << academic_border;
    out << academic_border << empty_block << academic_border << "TIMS" << three_empty << endl;

    // printing the third row of board
    out << divider << empty_block << "EV1" << four_empty << empty_block << "EV2";
    out << "EV3" << four_empty << empty_block << "PHYS" << three_empty << "B1" << five_empty;
    out << empty_block << "B1" << five_empty << empty_block << endl;

    // printing the fourth and fifth row of board
    out << divider;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 11; ++j) {
            out << empty_block;
        }
        out << endl;
    }

    // printing bottom of top row
    out << divider;
    for (int i = 0; i < 11; ++i) {
        out << block_bottom;
    }
    out << endl;


    // second row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "OPT" << four_empty << empty_middle_section << "EIT" << four_empty << endl; // block_row3
    out << blank_middle_section << endl; // block_row4
    out << middle_block_bottom << endl; // block_row5

    // third row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "BMH" << four_empty << empty_middle_section << "EIT" << four_empty << endl; // block_row3
    out << blank_middle_section << endl; // block_row4
    out << middle_block_bottom << endl; // block_row5

    // fourth row of blocks
    out << divider << "SLC" << four_empty << empty_middle_section << "SLC" << four_empty << endl;
    for (int i = 0; i < 3; ++i) {
        // printing the empty section in the middle
        out << blank_middle_section << endl;
    }
    out << middle_block_bottom;


    // fifth row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "LHI" << four_empty << empty_middle_section << "C2" << five_empty << endl; // block_row3
    out << divider << empty_block << wat_surround << string("_", 45); // block_row4
    out << " " << wat_surround << empty_block << endl;
    out << divider << empty_block << wat_surround << string(" ", 45) << divider;
    out << wat_surround << block_bottom << endl;

    // sixth row of blocks
    out << divider << "UWP" << four_empty << wat_surround << " #   #  ##  #####"; // block_row1
    out << "  ###  ###   ###  #   #   # |" << wat_surround << "REV" << four_empty << endl;
    out << divider << empty_block << wat_surround << " #   # #  #   #   #   # #  #"; // block_row2
    out << " #   # #   #   # |" << wat_surround << empty_block << endl;
    out << divider << empty_block << wat_surround << " # # # ####   #   #   # ###  #"; // block_row3
    out << "   # #    # #  |" << wat_surround << empty_block << endl;
    out << divider << empty_block << wat_surround << " # # # #  #   #   #   # #"; // block_row4
    out << "    #   # #     #   |" << wat_surround << empty_block << endl;
    out << divider << block_bottom << wat_surround << " #### #  #   #    ###  #"; // block_row5
    out << "     ###  ## #  #   |" << wat_surround << block_bottom << endl;

    // seventh row of blocks
    out << divider << empty_block << wat_surround << string("_", 45) << divider; // block_row1
    out << wat_surround << "NEEDLES" << divider << endl;
    out << divider << academic_border << empty_middle_section << "HALL" << three_empty << endl; // block_row2
    out << divider << "CPH" << four_empty << empty_middle_section << empty_block << endl; // block_row3
    out << blank_middle_section << endl; // block_row4
    out << middle_block_bottom << endl; // block_row5

    // eighth row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "DWE" << four_empty << empty_middle_section << "|MC" << five_empty << endl; // block_row3 
    out << blank_middle_section << endl; // block_row4
    out << middle_block_bottom << endl; // block_row5

    // ninth row of blocks
    out << divider << "PAC" << four_empty << empty_middle_section << "COOP" << three_empty << endl; // block_row1
    out << divider << empty_block << empty_middle_section << "FEE" << four_empty << endl;
    out << blank_middle_section << endl;
    out << blank_middle_section << endl;
    out << middle_block_bottom << endl;

    // tenth row of blocks
    out << blank_middle_section << endl;
    out << middle_academic_border << endl;
    out << divider << "RCH" << four_empty << empty_middle_section << "DC" << five_empty << endl;
    out << blank_middle_section << endl;
    out << divider << block_bottom << string(string("_", sqr_len), 9) << divider << block_bottom << endl;

    // last row of blocks
    out << divider << "DC TIMS|" << empty_block << empty_block << "NEEDLES" << divider; // row_1
    out << empty_block << "MKV" << four_empty << "TUITION" << divider << empty_block;
    out << "SLC" << four_empty << empty_block << "COLLECT" << divider << endl;

    out << "Line" << three_empty << academic_border << academic_border << "HALL"; // row_2
    out << academic_border << empty_block << empty_block << academic_border << empty_block;
    out << academic_border << "OSAP" << three_empty << endl;

    out << empty_block << "HH" << five_empty << "PAS" << four_empty << empty_block; // row_3
    out << "ECH" << four_empty << empty_block << empty_block << "ML" << five_empty;
    out << empty_block << "AL" << five_empty << empty_block << endl;

    out << divider; // row_4
    for (int i = 0; i < 11; ++i) {
        out << empty_block;
    }
    out << endl;

    out << divider;
    for (int i = 0; i < 11; ++i) {
        out << block_bottom;
    }
    out << endl;

    return out;
}
