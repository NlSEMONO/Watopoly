#include <sstream>
#include <fstream>
#include "game.h"
#include "slcrng.h"
#include "needlesrng.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"
#include <stdexcept>
using namespace std;

const int BOARD_SIZE = 40;

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

void Game::transaction(Player *trader, string to_trade, string to_get, int playerTurn) {
    if (isdigit(to_trade[0])) {
        // changing money
        int money_traded = stoi(to_trade);
        players[playerTurn]->changeCash(money_traded, false);
        trader->changeCash(money_traded, true);

        b.getSquare(to_get)->setOwner(players[playerTurn].get());

        // changing property
        if (b.isAcademic(b.getIndex(to_get))) {
        } else if (b.isGym(b.getIndex(to_get))) {
            Gym *gym = dynamic_cast<Gym *>(b.getSquare(to_get));
            gym->setOwner(players[playerTurn].get());
        } else {
            Residence *res = dynamic_cast<Residence *>(b.getSquare(to_get));
            res->setOwner(players[playerTurn].get());
        }
    } else if (isdigit(to_get[0])) {
        // changing money
        int money_recieved = stoi(to_get);
        players[playerTurn]->changeCash(money_recieved, true);
        trader->changeCash(money_recieved, false);

        // changing property
        if (b.isAcademic(b.getIndex(to_trade))) {
            building->setOwner(trader);
        } else if (b.isGym(b.getIndex(to_trade))) {
            Gym *gym = dynamic_cast<Gym *>(b.getSquare(to_get));
            gym->setOwner(trader);
        } else {
            Residence *res = dynamic_cast<Residence *>(b.getSquare(to_get));
            res->setOwner(trader);
        }
    } else {
        if (b.isAcademic(b.getIndex(to_get))) {
            Academic *building = dynamic_cast<Academic *>(b.getSquare(to_get));
            if (b.isAcademic())
        }
    }
}

int Game::handleMove(Player* p, int rollSum) {
    int newPos = (p->getPlayerPostion() + rollSum) % BOARD_SIZE;
    p->setPlayerPostion(newPos);
    Square* tile = b.getSquare(newPos);
    if (b.isOwnable(newPos)) {
        // unowned property
        if (tile->getOwner() == nullptr) {
            cout << tile->getName() << " is unowned. Your balance is " << p->getLiquidCash();
            cout << ". It costs " << tile->getCost() << ". Would you like to buy it? (y/n)" << endl;
            string resp;
            cin >> resp;
            if (resp == "y") {
                tile->buy(p);
                if (b.isGym(newPos)) gymsOwned[p]++;
                else if (b.isResidence(newPos)) residenceOwned[p]++;
                int owed = p->getLiquidCash() * -1;
                if (owed > 0) {
                    cout << "You owe the bank " << owed << " money. Please mortgage properties, sell improvements or declare bankruptcy." << endl;
                    p->setLiquidCash(0);
                    return owed;
                }
                return 0;
            }
        }
        // owned property
        else {
            int rentOwed = 0;
            Player* owner = tile->getOwner();
            if (b.isGym(newPos)) {
                Gym* gymPtr = dynamic_cast<Gym*>(tile);
                rentOwed = gymPtr->getRent(gymsOwned[owner], rollSum);
            } else if (b.isResidence(newPos)) {
                Residence* resPtr = dynamic_cast<Residence*>(tile);
                rentOwed = resPtr->getRent(residenceOwned[owner]);
            } else {
                Academic* acaPtr = dynamic_cast<Academic*>(tile);
                rentOwed = acaPtr->getRent();
            }
            cout << tile->getName() << " is owned by: " << owner->getPlayerName() << " paying them: " << rentOwed << endl;
            
            // TODO: finish paying owner
        }
    } else if (b.isSLC(newPos)) {

    } else if (b.isNeedles(newPos)) {

    }
    return 0;
}

void Game::play() {
    //CLI Interpreter
    string cmdWhole;
    int playerTurn = 0;
    int moneyOwed = 0;
    bool hasRolled = false;
    int snakeEyes = 0;
    bool jailMsg = false;

    while(getline(cin, cmdWhole)){
        istringstream iss2{cmdWhole};
        string cmd;
        iss2 >> cmd;
        Player* currPlayer = players[playerTurn].get();
        
        
        // implement jail
        if (jailedTurns.count(currPlayer) == 1 && !jailMsg) {
            cout << "You are in jail, and you have " << numCups[currPlayer]  << " cups. Options: "<< endl;

            string resp;
            cin >> resp;

            jailMsg = true;
        }
        // implement
        if (cmd == "roll"){
            // b.makeMove(players[playerTurn].get());  
            int roll1 = dice.eventToInt(dice.generateEvent());
            int roll2 = dice.eventToInt(dice.generateEvent());

            if (hasRolled) {
                if (roll1 == roll2 && snakeEyes == 2) {
                    cout << "3 snake eyes in a row, sending you to jail!" << endl;
                    currPlayer->setPlayerPostion(b.getIndex("DC Tims Line"));
                } else if (roll1 == roll2) {
                    moneyOwed = handleMove(currPlayer, roll1 + roll2);
                    ++snakeEyes;
                } else {
                    moneyOwed = handleMove(currPlayer, roll1 + roll2);
                    hasRolled = true;
                }
            } else cerr << "You've already rolled this turn." << endl;
        } else if (cmd == "next"){
            if (!hasRolled || moneyOwed > 0) {
                cerr << "You can't end your turn yet!" << endl;
                continue;
            }
            playerTurn++;
            if (playerTurn == playerCount){
                playerTurn = 0;
            }
            hasRolled = false;
            jailMsg = false;
            snakeEyes = 0;
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
                    cin >> response;

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
                    cin >> response;

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
            Player* curr = players[playerTurn].get();
            int pos = curr->getPlayerPostion();
            
            if (b.isAcademic(pos)) {
                Academic* sq = dynamic_cast<Academic*>(b.getSquare(pos));
                if (sq->getOwner() == curr) {
                    string setting; 
                    iss2 >> setting;

                    if (setting == "buy" && curr->canAfford(sq->getUpgrade_cost())) { 
                        if (sq->getUpgradeLevel() < 5) sq->upgrade();
                        else cerr << "You can't upgrade this property anymore." << endl;
                    } else if (setting == "sell") {
                        if (sq->getUpgradeLevel() > 0) sq->sellUpgrade();
                        else cerr << "You can't sell any more upgardes from this property." << endl; 
                    } else cerr << "you can't afford to upgrade this property." << endl;
                } else cerr << "You don't own this property!" << endl;
            } else cerr << "You can't upgrade this property." << endl;
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
            string filename;
            iss2 >> filename;
            ofstream out;
            out.open(filename);

            // player1 char TimsCups money position
            for (int i = 0; i < players.size(); ++i) {
                Player* curr = players[i].get();
                out << curr->getPlayerName() << " " << curr->getSymbol() << " " << numCups[curr] << " " << curr->getLiquidCash() << curr->getPlayerPostion() << endl;
            }
            b.saveProperties(out);
            out.close();
        } 
        // else {
        //     throw runtime_error{"Not a valid command"};
        // }
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
const string wat_surround = string(12, ' ');

// Watopoly Strings
const string wat_1 = " #   #  ##  #####";
const string wat_2 = "  ###  ###   ###  #   #   # |";
const string wat_3 = " #   # #  #   #   #   # #  #";
const string wat_4 = " #   # #   #   # |";
const string wat_5 = " # # # ####   #   #   # ###  #";
const string wat_6 = "   # #    # #  |";
const string wat_7 = " # # # #  #   #   #   # #";
const string wat_8 = "    #   # #     #   |";
const string wat_9 = " ##### #  #   #    ###  #";
const string wat_10 = "     ###  ## #  #   |";


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

    // printing the fourth row of board (Players per board)
    out << divider;
    out << game.b.getSquare("Goose Nesting")->printPlayers();
    out << game.b.getSquare("EV1")->printPlayers();
    out << game.b.getSquare("NEEDLES HALL2")->printPlayers();
    out << game.b.getSquare("EV2")->printPlayers();
    out << game.b.getSquare("EV3")->printPlayers();
    out << game.b.getSquare("V1")->printPlayers();
    out << game.b.getSquare("PHYS")->printPlayers();
    out << game.b.getSquare("B1")->printPlayers();
    out << game.b.getSquare("CIF")->printPlayers();
    out << game.b.getSquare("B2")->printPlayers();
    out << game.b.getSquare("GO TO TIMS")->printPlayers();
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
    out << divider << game.b.getSquare("OPT")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("EIT")->printPlayers() << endl;
    out << middle_block_bottom << endl; // block_row5

    // third row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "BMH" << four_empty << empty_middle_section << "ESC" << four_empty << endl; // block_row3
    out << divider << game.b.getSquare("BMH")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("ESC")->printPlayers() << endl;
    out << middle_block_bottom << endl; // block_row5

    // fourth row of blocks
    out << divider << "SLC" << four_empty << empty_middle_section << "SLC" << four_empty << endl; // block_row1
    for (int i = 0; i < 2; ++i) {
        // printing the empty section in the middle
        out << blank_middle_section << endl;
    }

    out << divider << game.b.getSquare("SLC2")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("SLC3")->printPlayers() << endl;
    out << middle_block_bottom << endl; // block_row5


    // fifth row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "LHI" << four_empty << empty_middle_section << "C2" << five_empty << endl; // block_row3
    out << divider << game.b.getSquare("LHI")->printPlayers() << wat_surround << " " << string(45, '_'); // block_row4
    out << " " << wat_surround + divider << game.b.getSquare("C2")->printPlayers() << endl;
    out << divider << block_bottom << wat_surround + divider << string(45, '_') << divider; // block_row5
    out << wat_surround + divider << block_bottom << endl;


    // sixth row of blocks
    out << divider << "UWP" << four_empty << wat_surround + divider << wat_1; // block_row1
    out << wat_2 << wat_surround + divider << "REV" << four_empty << endl;
    out << divider << empty_block << wat_surround + divider << wat_3; // block_row2
    out << wat_4 << wat_surround + divider << empty_block << endl;
    out << divider << empty_block << wat_surround + divider << wat_5; // block_row3
    out << wat_6 << wat_surround + divider << empty_block << endl;
    out << divider << game.b.getSquare("UWP")->printPlayers() << wat_surround + divider << wat_7; // block_row4
    out << wat_8 << wat_surround + divider << game.b.getSquare("REV")->printPlayers() << endl;
    out << divider << block_bottom << wat_surround + divider << wat_9; // block_row5
    out << wat_10 << wat_surround + divider << block_bottom << endl;

    // seventh row of blocks
    out << divider << empty_block << wat_surround + divider << string(45, '_') << divider; // block_row1
    out << wat_surround + divider << "NEEDLES" << divider << endl;
    out << divider << academic_border << empty_middle_section << "HALL" << three_empty << endl; // block_row2
    out << divider << "CPH" << four_empty << empty_middle_section << empty_block << endl; // block_row3
    out << divider << game.b.getSquare("CPH")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("NEEDLES HALL3")->printPlayers() << endl;
    out << middle_block_bottom << endl; // block_row5

    // eighth row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "DWE" << four_empty << empty_middle_section << "MC" << five_empty << endl; // block_row3
    out << divider << game.b.getSquare("DWE")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("MC")->printPlayers() << endl; 
    out << middle_block_bottom << endl; // block_row5

    // ninth row of blocks
    out << divider << "PAC" << four_empty << empty_middle_section << "COOP" << three_empty << endl; // block_row1
    out << divider << empty_block << empty_middle_section << "FEE" << four_empty << endl; // block_row2
    out << blank_middle_section << endl; // block_row3
    out << divider << game.b.getSquare("PAC")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("COOP FEE")->printPlayers() << endl; 
    out << middle_block_bottom << endl; // block_row5

    // tenth row of blocks
    out << blank_middle_section << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "RCH" << four_empty << empty_middle_section << "DC" << five_empty << endl; // block_row3
    out << divider << game.b.getSquare("RCH")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("DC")->printPlayers() << endl; 
    out << divider << block_bottom << string(9 * (sqr_len + 1) - 1, '_') << divider << block_bottom << endl; // block_row5

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

    // printing row4
    out << divider;
    out << game.b.getSquare("DC Tims Line")->printPlayers();
    out << game.b.getSquare("HH")->printPlayers();
    out << game.b.getSquare("PAS")->printPlayers();
    out << game.b.getSquare("NEEDLESHALL1")->printPlayers();
    out << game.b.getSquare("ECH")->printPlayers();
    out << game.b.getSquare("MKV")->printPlayers();
    out << game.b.getSquare("TUITION")->printPlayers();
    out << game.b.getSquare("ML")->printPlayers();
    out << game.b.getSquare("SLC1")->printPlayers();
    out << game.b.getSquare("AL")->printPlayers();
    out << game.b.getSquare("COLLECT OSAP")->printPlayers();
    out << endl;

    out << divider;
    for (int i = 0; i < 11; ++i) {
        out << block_bottom;
    }
    out << endl;

    return out;
}
