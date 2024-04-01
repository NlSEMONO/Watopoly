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

void Game::initPlayers() {
    //Player Name Init
    string nameOfPLayer;
    int i = 0;
    vector<char> possibleSymbols = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
    vector<string> names = {};
    int cnt = 0;
    while(i < playerCount){
        cout << "Name of player " << i << ":" << endl;
        cin >> nameOfPLayer;
        cnt = count(names.begin(), names.end(), nameOfPLayer);
        if (cin && cnt == 0){
          players.push_back(unique_ptr<Player>{new Player{nameOfPLayer, '\0', 1500, 0, 0, 0}});
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
    while(j < playerCount){
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
                j++;
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

    cout << "Game has been intialized with " << playerCount << "!" << endl;
}

void Game::play() {
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
            string player_2;
            string to_give;
            string to_get;
            iss2 >> player_2 >> to_give >> to_get;
            Player *trade_from = nameToPlayer[player_2];

            if (isdigit(to_give[0]) && isdigit(to_get[0])) {
                // trading money for money
                throw runtime_error("Invalid trade");
            } else if (isdigit(to_give[0])) {
                int money_given = stoi(to_give);
                if (players[playerTurn]->canAfford(money_given)) {
                    string response;
                    iss2 >> response;

                    if (response == "accept") {
                        trade_from->changeCash(money_given, true);
                        players[playerTurn]->changeCash(money_given, false);
                        b.getSquare(to_get)->addPlayer(players[playerTurn].get());
                        b.getSquare(to_get)->removePlayer(trade_from);
                        // accept
                    } else {
                        break;
                    }
                }
            } else if (isdigit(to_get[0])) {
                int money_recieved = stoi(to_get);
                if (trade_from->canAfford(money_recieved)){
                    string response;
                    iss2 >> response;

                    if (response == "accept") {
                        trade_from->changeCash(money_recieved, false);
                        players[playerTurn]->changeCash(money_recieved, true);
                        b.getSquare(to_give)->addPlayer(trade_from);
                        b.getSquare(to_give)->removePlayer(players[playerTurn].get());
                        // accept
                    } else {
                        break;
                    }
                }
            } else {
                string response;
                iss2 >> response;

                if (response == "accept") {
                    b.getSquare(to_give)->addPlayer(trade_from);
                    b.getSquare(to_give)->removePlayer(players[playerTurn].get());

                    b.getSquare(to_get)->addPlayer(players[playerTurn].get());
                    b.getSquare(to_get)->removePlayer(trade_from);
                    // accept
                } else {
                    break;
                }
            }

           
        } else if (cmd == "improve"){
            
        } else if (cmd == "mortgage"){
            
        } else if (cmd == "unmortgage"){
            
        } else if (cmd == "bankrupt"){
            
            
        } else if (cmd == "assets"){
            //Logic to check is player is paying tuition if yes:
            cout << "Player " << players[playerTurn]->getPlayerName() << " has this much cash: " << players[playerTurn]->getLiquidCash() << endl;
            cout << "Player " << players[playerTurn]->getPlayerName() << " has these properties " << endl;
            vector<Square*> playerAssets;
            b.getOwnedSquares(players[playerTurn].get(), playerAssets);
            for (int i = 0; i < playerAssets.size(); i++){
                cout << playerAssets[i]->getName() << endl;
            }
            cout << "Player " << players[playerTurn]->getPlayerName() << " total assets are: " << players[playerTurn]->getTotalAssetsValue() << endl;

        } else if (cmd == "all"){
            //Logic to check is player is paying tuition if yes:
            for (int j = 0; j < playerCount; j++){
                cout << "Player " << players[j]->getPlayerName() << " has this much cash: " << players[j]->getLiquidCash() << endl;
                cout << "Player " << players[j]->getPlayerName() << " has these properties " << endl;
                vector<Square*> playerAssets;
                b.getOwnedSquares(players[j].get(), playerAssets);
                for (int i = 0; i < playerAssets.size(); i++){
                    cout << playerAssets[i]->getName() << endl;
                }
                cout << "Player " << players[j]->getPlayerName() << " total assets are: " << players[j]->getTotalAssetsValue() << endl;
                cout << endl;
            }
            
        } else if (cmd == "save"){
            
        } 
        // else {
        //     throw runtime_error{"Not a valid command"};
        // }

        playerTurn++;
        if (playerTurn == playerCount){
            playerTurn = 0;
        }
    }
}

const int sqr_len = 7;
const int board_len = 11;

const char divider = '|';
const string academic_border = string(sqr_len, '-') + divider;
const string empty_block = string(sqr_len, ' ') + divider;
const string block_bottom = string(sqr_len, '_') + divider;
const string three_empty = string(3, ' ') + divider;
const string four_empty = string(4, ' ') + divider;
const string five_empty = string(5, ' ') + divider;
const string empty_middle_section = string((8 * 9) - 1, ' ') + divider;
const string blank_middle_section = divider + empty_block + empty_middle_section + empty_block;
const string middle_block_bottom = divider + block_bottom + empty_middle_section + block_bottom;
const string middle_academic_border = divider + academic_border + empty_middle_section + academic_border;
const string wat_surround = string(12, ' ') + divider;

ostream &operator<<(ostream &out, Game &game) {
    out << string(8 * 11, '_') << endl; // top border

    // first row of blocks 
    // printing the first row of board
    out << "|Goose  |" << empty_block << "NEEDLES|" << empty_block;
    out << empty_block << "V1" << five_empty << empty_block;
    out << empty_block << "CIF" << four_empty << empty_block;
    out << "GO TO  |" << endl;

    // printing the second row of board
    out << divider << "Nesting" << divider << academic_border << "HALL" << three_empty;
    out << academic_border << academic_border << empty_block << academic_border;
    out << academic_border << empty_block << academic_border << "TIMS" << three_empty << endl;

    // printing the third row of board
    out << divider << empty_block << "EV1" << four_empty << empty_block << "EV2" << four_empty;
    out << "EV3" << four_empty << empty_block << "PHYS" << three_empty << "B1" << five_empty;
    out << empty_block << "B1" << five_empty << empty_block << endl;

    // printing the fourth row of board
    out << divider;
    for (int j = 0; j < 11; ++j) {
        out << empty_block;
    }
    out << endl;

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
    out << divider << empty_block << wat_surround << string(45, '_'); // block_row4
    out << " " << wat_surround << empty_block << endl;
    out << divider << empty_block << wat_surround << string(45, '_') << divider;
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
    out << divider << block_bottom << wat_surround << " ##### #  #   #    ###  #"; // block_row5
    out << "     ###  ## #  #   |" << wat_surround << block_bottom << endl;

    // seventh row of blocks
    out << divider << empty_block << wat_surround << string(45, '_') << divider; // block_row1
    out << wat_surround << "NEEDLES" << divider << endl;
    out << divider << academic_border << empty_middle_section << "HALL" << three_empty << endl; // block_row2
    out << divider << "CPH" << four_empty << empty_middle_section << empty_block << endl; // block_row3
    out << blank_middle_section << endl; // block_row4
    out << middle_block_bottom << endl; // block_row5

    // eighth row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "DWE" << four_empty << empty_middle_section << "MC" << five_empty << endl; // block_row3 
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
    out << divider << block_bottom << string(9 * (sqr_len + 1) - 1, '_') << divider << block_bottom << endl;

    // last row of blocks
    out << divider << "DC TIMS|" << empty_block << empty_block << "NEEDLES" << divider; // row_1
    out << empty_block << "MKV" << four_empty << "TUITION" << divider << empty_block;
    out << "SLC" << four_empty << empty_block << "COLLECT" << divider << endl;

    out << divider << "Line" << three_empty << academic_border << academic_border << "HALL" << three_empty; // row_2
    out << academic_border << empty_block << empty_block << academic_border << empty_block;
    out << academic_border << "OSAP" << three_empty << endl;

    out << divider << empty_block << "HH" << five_empty << "PAS" << four_empty << empty_block; // row_3
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
