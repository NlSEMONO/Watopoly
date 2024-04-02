#include <sstream>
#include <fstream>
#include "game.h"
#include "slcrng.h"
#include "needlesrng.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"
#include "goosenest.h"
#include <stdexcept>
#include <iostream>
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

// transaction(trader, to_trade, to_get, playerTurn) will initiate a trade transaction
// between the currentPlayer who can be accessed through playerTurn and trader.
// The current player will send to_trade to trader and will get to_get in return from
// trader.
void Game::transaction(Player *trader, string to_trade, string to_get, int playerTurn) {
    if (isdigit(to_trade[0])) {
        // changing money
        int money_traded = stoi(to_trade);
        players[playerTurn]->changeCash(money_traded, false);
        trader->changeCash(money_traded, true);

        // changing property
        b.getSquare(to_get)->setOwner(players[playerTurn].get());
    } else if (isdigit(to_get[0])) {
        // changing money
        int money_recieved = stoi(to_get);
        players[playerTurn]->changeCash(money_recieved, true);
        trader->changeCash(money_recieved, false);
        // changing property
        b.getSquare(to_trade)->setOwner(trader);

    } else {
        b.getSquare(to_get)->setOwner(players[playerTurn].get());
        b.getSquare(to_trade)->setOwner(trader);
    }
}


// helper function to calculate how much money game p owes bank/other player.
int processOwed(Player* p, string who) {
    int owed = p->getLiquidCash() * -1;
    if (owed > 0) {
        cout << "You owe " << who << " " << owed << " money. Please mortgage properties, sell improvements or declare bankruptcy." << endl;
        p->setLiquidCash(0);
        return owed;
    }
    return 0;
}

void Game::sendToJail(Player* p) {
    p->setPlayerPostion(b.getIndex("DC Tims Line"));
    jailedTurns[p] = 0;
}

int Game::handleAuction(size_t start, Square* prize) {
    std::map<Player*, bool> outOfAuction;
    cout << "Starting auction for " << prize->getName() << endl;
    int highest = 0;
    Player* winner = players[start].get();
    while (outOfAuction.size() < players.size() - 1) {
        Player* curr = players[start].get();
        if (outOfAuction.count(curr) != 0) continue; // go next player if player is out
        cout << curr->getPlayerName() << " do you want to bid? Highest bid is: $" << highest << " (y/n)" << endl;
        string resp;
        while (resp != "y" && resp != "n") {
            cout << "Please enter (y/n)." << endl;
            std::cin >> resp;
        }
        if (resp == "n") {
            outOfAuction[curr] = true;
            continue;
        }
        cout << "How much do you want to bid? Your cash is: $" << curr->getLiquidCash() << endl;
        int amt = -100;
        std::cin >> amt;
        if (amt != -100 && highest < amt && amt <= curr->getLiquidCash()) {
            highest = amt;
            winner = curr;
        } else {
            cerr << "Bid is too low/invalid, withdrawing from auction." << endl;
            outOfAuction[curr] = true;
            continue;
        }
    }
    cout << "Winner is: " << winner->getPlayerName() << " with bid $" << highest << "." << endl;
    winner->setLiquidCash(winner->getLiquidCash() - highest);
    prize->setOwner(winner);
    return processOwed(winner, "the bank");
}

int Game::handleOwnable(Player* p, int newPos, int rollSum) {
    Square* tile = b.getSquare(newPos);

    // unowned property
    if (tile->getOwner() == nullptr) {
        cout << tile->getName() << " is unowned. Your balance is " << p->getLiquidCash();
        cout << ". It costs " << tile->getCost() << ". Would you like to buy it? (y/n)" << endl;
        string resp;
        std::cin >> resp;
        while (resp != "y" && resp != "n") {
            cerr << "Invalid input, please enter again (y/n)." << endl;
            cin >> resp;
        }
        if (resp == "y") {
            tile->buy(p);
            if (b.isGym(newPos)) gymsOwned[p]++;
            else if (b.isResidence(newPos)) residenceOwned[p]++;
            return processOwed(p, "the bank");
        } else {
            return handleAuction((currPlayer + 1) % players.size(), tile);
        }
    }
    // owned property
    else {
        int rentOwed = 0;
        Player* owner = tile->getOwner();
        cout << tile->getName() << " is owned by: " << owner->getPlayerName() << " paying them: ";
        if (b.isGym(newPos)) {
            Gym* gymPtr = dynamic_cast<Gym*>(tile);
            rentOwed = gymPtr->getRent(gymsOwned[owner], rollSum);
            cout << rentOwed << endl;
            gymPtr->payRent(p, gymsOwned[owner], rollSum);
        } else if (b.isResidence(newPos)) {
            Residence* resPtr = dynamic_cast<Residence*>(tile);
            rentOwed = resPtr->getRent(residenceOwned[owner]);
            cout << rentOwed << endl;
            resPtr->payRent(p, residenceOwned[owner]);
        } else {
            Academic* acaPtr = dynamic_cast<Academic*>(tile);
            rentOwed = acaPtr->getRent();
            cout << rentOwed << endl;
            acaPtr->payRent(p, b.ownsAll(p, newPos));
        }
        return processOwed(p, owner->getPlayerName());
    }
}

int Game::handleSLC(Player* p) {
    Event evt = rngSLC.generateEvent();
    if (cupsDistributed >= 4) while (evt == Event::OUTOFTIMS) evt = rngSLC.generateEvent();
    if (evt == Event::OUTOFTIMS) {
        cout << "You drew an SLC card and got a get out of Tim's line card!" << endl;
        ++numCups[p];
        ++cupsDistributed;
    } else if (evt == Event::MB3) {
        cout << "You drew an SLC card telling you to move back 3 spaces." << endl;
        this->handleMove(p, -3);
    } else if (evt == Event::MB2) {
        cout << "You drew an SLC card telling you to move back 2 spaces." << endl;
        this->handleMove(p, -2);
    } else if (evt == Event::MB1) {
        cout << "You drew an SLC card telling you to move back 1 space." << endl;
        this->handleMove(p, -1);
    } else if (evt == Event::MF1) {
        cout << "You drew an SLC card telling you to move forward 1 space." << endl;
        this->handleMove(p, 1);
    } else if (evt == Event::MF2) {
        cout << "You drew an SLC card telling you to move forward 2 spaces." << endl;
        this->handleMove(p, 2);
    } else if (evt == Event::MF3) {
        cout << "You drew an SLC card telling you to move forward 3 spaces." << endl;
        this->handleMove(p, 3);
    } else if (evt == Event::MDC_TIMS) {
        cout << "You drew an SLC card and must now wait in DC Tim's Line :(" << endl;
        sendToJail(p);
    } else if (evt == Event::MCOLLECT_OSAP) {
        this->handleMove(p, 40 - p->getPlayerPostion());
    }
    return 0;
}

int Game::handleNeedles(Player* p) {
    Event evt = rngSLC.generateEvent();
    if (cupsDistributed >= 4) while (evt == Event::OUTOFTIMS) evt = rngSLC.generateEvent();
    if (evt == Event::OUTOFTIMS) {
        cout << "You drew a Needles Hall card and got a get out of Tim's line card!" << endl;
        ++numCups[p];
        ++cupsDistributed;
    } else if (evt == Event::CM200) {
        const int payment = 200;
        cout << "You drew a Needles Hall card and need to pay $"<< payment << "!" << endl;
        p->changeCash(-payment); 
        GooseNest* gn = dynamic_cast<GooseNest*>(b.getSquare(b.getIndex("Goose Nesting")));
        gn->setAccumulated(gn->getAccumulated() - payment);
    } else if (evt == Event::CM100) {
        const int payment = 100;
        cout << "You drew a Needles Hall card and need to pay $"<< payment << "!" << endl;
        p->changeCash(-payment); 
        GooseNest* gn = dynamic_cast<GooseNest*>(b.getSquare(b.getIndex("Goose Nesting")));
        gn->setAccumulated(gn->getAccumulated() - payment);
    } else if (evt == Event::CM50) {
        const int payment = 50;
        cout << "You drew a Needles Hall card and need to pay $"<< payment << "!" << endl;
        p->changeCash(-payment); 
        GooseNest* gn = dynamic_cast<GooseNest*>(b.getSquare(b.getIndex("Goose Nesting")));
        gn->setAccumulated(gn->getAccumulated() - payment);
    } else if (evt== Event::CP25) {
        const int payment = 25;
        cout << "You drew a Needles Hall card and have recieved $"<< payment << "!" << endl;
        p->changeCash(payment);
    } else if (evt == Event::CP50) {
        const int payment = 50;
        cout << "You drew a Needles Hall card and have recieved $"<< payment << "!" << endl;
        p->changeCash(payment);
    } else if (evt == Event::CP100) {
        const int payment = 50;
        cout << "You drew a Needles Hall card and have recieved $"<< payment << "!" << endl;
        p->changeCash(payment);
    } else if (evt == Event::CP200) {
        const int payment = 200;
        cout << "You drew a Needles Hall card and have recieved $"<< payment << "!" << endl;
        p->changeCash(payment);
    }

    return processOwed(p, "the bank");
}

int Game::handleMove(Player* p, int rollSum) {
    int newPos = p->getPlayerPostion() + rollSum;
    if (newPos >= 40) {
        newPos %= 40;
        cout << "Collected OSAP." << endl;
        p->changeCash(200);
    }
    p->setPlayerPostion(newPos);

    if (b.isOwnable(newPos)) { // academic/residence/gym
        return handleOwnable(p, newPos, rollSum);
    } else if (b.isSLC(newPos)) { // SLC square
        return handleSLC(p);
    } else if (b.isNeedles(newPos)) { // Needles Hall square
        return handleNeedles(p);
    } else if (b.getIndex("Goose Nesting") == newPos) { // free parking
        GooseNest* gn = dynamic_cast<GooseNest*>(b.getSquare(newPos));
        cout << "You landed on Goose Nesting. Collecting $" << gn->getAccumulated() << "." << endl;
        p->changeCash(gn->getAccumulated());
        gn->setAccumulated(0);
    } else if (b.getIndex("Tuition") == newPos) { // tuition
        cout << "Pay tuition. Do you want to (1) pay 10\% of your cash or (2) $300?" << endl;
        int opt = -1;
        cin >> opt;
        while (opt != 1 && opt != 2) {
            cout << "Please enter 1 or 2" << endl;
            cin >> opt;
        }
        GooseNest* gn = dynamic_cast<GooseNest*>(b.getSquare(newPos));
        int to_pay = 300;
        if (opt == 1) to_pay = p->getLiquidCash() / 10;
        p->changeCash(-to_pay);
        gn->setAccumulated(gn->getAccumulated() + to_pay);

        return processOwed(p, "the bank");
    } else if (b.getIndex("Coop Fee") == newPos) { // coop fee
        const int coopFee = 150;
        cout << "You landed on Coop Fee. You must pay $" << coopFee << "." << endl;
        GooseNest* gn = dynamic_cast<GooseNest*>(b.getSquare(newPos));
        p->changeCash(-coopFee);
        gn->setAccumulated(gn->getAccumulated() + coopFee);

        return processOwed(p, "the bank");
    } else if (b.getIndex("Go To Tims") == newPos) { // go to tims
        cout << "Uh Oh, you landed on Go to DC Tim's Line." << endl;
        sendToJail(p);
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
            if (jailedTurns[currPlayer] == 3) {
                cout << "You've waited 3 turns in jail. You may now leave jail." << endl;
                jailedTurns.erase(currPlayer);
            } else {
                cout << "You are in jail, and you have " << numCups[currPlayer]  << " cups. Options: "<< endl;
                int resp = 55;
                do {
                    cout << "(1) - Use cup (You have: " << numCups[currPlayer] << ")." << endl;
                    cout << "(2) - Pay $50" << endl;
                    cout << "other - proceed to rolling" << endl;
                    cin >> resp;
                } while (resp == 1 && numCups[currPlayer] == 0);
                if (resp == 1 || resp == 2) {
                    if (resp == 1) {
                        --numCups[currPlayer];
                        --cupsDistributed;
                    }
                    else currPlayer->changeCash(-50);
                    jailedTurns.erase(currPlayer);
                    hasRolled = true;
                } 

                jailMsg = true;
                moneyOwed = processOwed(currPlayer, "the bank");
            }
        }

        cout << currPlayer->getPlayerName() << "'s turn. Options: " << (hasRolled ? "next," : "roll,") << "trade,improve,mortgage,mortgage,unmortgage,save,";
        cout << (moneyOwed > 0 ? "bankrupt" : "assets,all") << endl;
        // implement
        if (cmd == "roll"){
            // b.makeMove(players[playerTurn].get());  
            int roll1 = dice.eventToInt(dice.generateEvent());
            int roll2 = dice.eventToInt(dice.generateEvent());

            cout << "You rolled " << roll1 << " and " << roll2 << "." << endl;
            if (jailedTurns.count(currPlayer) == 1) {
                if (roll1 == roll2) {
                    cout << "You rolled snake eyes and are now out of jail." << endl;
                    jailedTurns.erase(currPlayer);
                }
                else {
                    cout << "You did not roll snake eyes, you are still in jail." << endl;
                    ++jailedTurns[currPlayer];
                }
                hasRolled = true;
            } else if (!hasRolled) {
                if (roll1 == roll2 && snakeEyes == 2) {
                    cout << "3 snake eyes in a row, sending you to jail!" << endl;
                } else if (roll1 == roll2) {
                    cout << "You rolled snake eyes and must roll again before ending your turn." << endl;
                    moneyOwed += handleMove(currPlayer, roll1 + roll2);
                    ++snakeEyes;
                } else {
                    moneyOwed += handleMove(currPlayer, roll1 + roll2);
                    hasRolled = true;
                }
            } else cerr << "You've already rolled this turn." << endl;
        } else if (cmd == "next"){
            if (!hasRolled) {
                cerr << "You must roll before ending your turn!" << endl;
                continue;
            }
            if (moneyOwed > 0) {
                cerr << "You still owe money, please buy/sell improvements, mortgage a property or declare bankruptcy." << endl;
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
                throw runtime_error("Invalid trade");
            } else {
                string response;
                cin >> response;

                if (response == "accept") {transaction(trade_from, to_give, to_get, playerTurn);}
                else {break;}
            }
        } else if (cmd == "improve"){
            Player* curr = players[playerTurn].get();
            int pos = curr->getPlayerPostion();
            
            if (b.isAcademic(pos)) {
                Academic* sq = dynamic_cast<Academic*>(b.getSquare(pos));
                if (sq->getOwner() == curr) {
                    if (b.ownsAll(curr, pos)) {
                        string setting; 
                        iss2 >> setting;

                        if (setting == "buy" && curr->canAfford(sq->getUpgrade_cost())) { 
                            if (sq->getUpgradeLevel() < 5) sq->upgrade();
                            else cerr << "You can't upgrade this property anymore." << endl;
                        } else if (setting == "sell") {
                            if (sq->getUpgradeLevel() > 0) sq->sellUpgrade();
                            else cerr << "You can't sell any more upgardes from this property." << endl; 
                        } else cerr << "you can't afford to upgrade this property." << endl;
                    } else cerr << "you don't own all properties of this monopoly!" << endl;
                } else cerr << "You don't own this property!" << endl;
            } else cerr << "You can't upgrade this property." << endl;
        } else if (cmd == "mortgage"){
            Player* curr = players[playerTurn].get();
            int pos = curr->getPlayerPostion();
            string propertyName;
            iss2 >> propertyName;
            if ((b.isAcademic(pos)) || (b.isGym(pos)) || (b.isResidence(pos))) {
                Square* sq = nullptr;
                if (b.isAcademic(pos)){
                    Academic* sq = dynamic_cast<Academic*>(b.getSquare(pos));
                } else if (b.isGym(pos)){
                    Gym* sq = dynamic_cast<Gym*>(b.getSquare(pos));
                } else {
                    Residence *sq = dynamic_cast<Residence*>(b.getSquare(pos));
                }

                if (sq->getOwner() == curr) {
                    if (!(sq->isMortgaged())){
                        sq->setMortgage(true);  //Redunant not needed, just there becuase i dont want to remove the virtual method
                        int mortgageBack = sq->getMortgageCost();

                        if (moneyOwed <= mortgageBack){
                            mortgageBack -= moneyOwed;
                            moneyOwed = 0;
                            sq->mortgage(mortgageBack);
                        } else {
                            moneyOwed -= mortgageBack;
                            mortgageBack = 0;
                            sq->mortgage(mortgageBack);
                        }
                    } else {
                        cerr << "This property is already mortgaged!" << endl;
                    }
                } else {
                    cerr << "You don't own this property!" << endl;
                }
            } else {
                cerr << "You can't mortgage this property." << endl;
            }


        } else if (cmd == "unmortgage"){
            Player* curr = players[playerTurn].get();
            int pos = curr->getPlayerPostion();
            string propertyName;
            iss2 >> propertyName;
            if ((b.isAcademic(pos)) || (b.isGym(pos)) || (b.isResidence(pos))) {
                Square* sq = nullptr;
                if (b.isAcademic(pos)){
                    Academic* sq = dynamic_cast<Academic*>(b.getSquare(pos));
                } else if (b.isGym(pos)){
                    Gym* sq = dynamic_cast<Gym*>(b.getSquare(pos));
                } else {
                    Residence *sq = dynamic_cast<Residence*>(b.getSquare(pos));
                }

                if (sq->getOwner() == curr) {
                    if ((sq->isMortgaged())){
                        sq->setMortgage(false);  //Redunant not needed, just there becuase i dont want to remove the virtual method
                        sq->unmortgage();
                    } else {
                        cerr << "This property is already unmortgaged!" << endl;
                    }
                } else {
                    cerr << "You don't own this property!" << endl;
                }
            } else {
                cerr << "You can't unmortgage this property." << endl;
            }
            
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

    // dynamically casted blocks
    Academic *EV1 = dynamic_cast<Academic *>(game.b.getSquare("EV1"));
    Academic *EV2 = dynamic_cast<Academic *>(game.b.getSquare("EV2"));
    Academic *EV3 = dynamic_cast<Academic *>(game.b.getSquare("EV3"));
    Academic *PHYS = dynamic_cast<Academic *>(game.b.getSquare("PHYS"));
    Academic *B1 = dynamic_cast<Academic *>(game.b.getSquare("B1"));
    Academic *B2 = dynamic_cast<Academic *>(game.b.getSquare("B2"));
    Academic *OPT = dynamic_cast<Academic *>(game.b.getSquare("OPT"));
    Academic *EIT = dynamic_cast<Academic *>(game.b.getSquare("EIT"));
    Academic *BMH = dynamic_cast<Academic *>(game.b.getSquare("BMH"));
    Academic *ESC = dynamic_cast<Academic *>(game.b.getSquare("ESC"));
    Academic *LHI = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *C2 = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *CPH = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *DWE = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *MC = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *RCH = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *DC = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *HH = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *PAS = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *ECH = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *ML = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    Academic *AL = dynamic_cast<Academic *>(game.b.getSquare("LHI"));
    
    out << string(8 * 11, '_') << endl; // top border

    // first row of blocks 
    // printing the first row of board
    out << "|Goose  |" << EV1->printImprovements() << "NEEDLES|" << EV2->printImprovements();
    out << EV3->printImprovements() << "V1" << five_empty << PHYS->printImprovements();
    out << B1->printImprovements() << "CIF" << four_empty << B2->printImprovements();
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
    out << divider << OPT->printImprovements() << empty_middle_section << EIT->printImprovements() << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "OPT" << four_empty << empty_middle_section << "EIT" << four_empty << endl; // block_row3
    out << divider << game.b.getSquare("OPT")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("EIT")->printPlayers() << endl;
    out << middle_block_bottom << endl; // block_row5

    // third row of blocks
    out << divider << BMH->printImprovements() << empty_middle_section << ESC->printImprovements() << endl; // block_row1
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
    out << divider << LHI->printImprovements() << empty_middle_section << C2->printImprovements() << endl; // block_row1
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
    out << divider << CPH->printImprovements() << wat_surround + divider << string(45, '_') << divider; // block_row1
    out << wat_surround + divider << "NEEDLES" << divider << endl;
    out << divider << academic_border << empty_middle_section << "HALL" << three_empty << endl; // block_row2
    out << divider << "CPH" << four_empty << empty_middle_section << empty_block << endl; // block_row3
    out << divider << game.b.getSquare("CPH")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("NEEDLES HALL3")->printPlayers() << endl;
    out << middle_block_bottom << endl; // block_row5

    // eighth row of blocks
    out << divider << DWE->printImprovements() << empty_middle_section << MC->printImprovements() << endl; // block_row1
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
    out << divider << RCH->printImprovements() << empty_middle_section << DC->printImprovements() << endl; // block_row1
    out << middle_academic_border << endl; // block_row2
    out << divider << "RCH" << four_empty << empty_middle_section << "DC" << five_empty << endl; // block_row3
    out << divider << game.b.getSquare("RCH")->printPlayers() << empty_middle_section; // block_row4
    out << game.b.getSquare("DC")->printPlayers() << endl; 
    out << divider << block_bottom << string(9 * (sqr_len + 1) - 1, '_') << divider << block_bottom << endl; // block_row5

    // last row of blocks
    out << divider << "DC TIMS|" << HH->printImprovements() << PAS->printImprovements() << "NEEDLES" << divider; // row_1
    out << ECH->printImprovements() << "MKV" << four_empty << "TUITION" << divider << ML->printImprovements();
    out << "SLC" << four_empty << AL->printImprovements() << "COLLECT" << divider << endl;

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

    out << divider; // block_row5
    for (int i = 0; i < 11; ++i) {
        out << block_bottom;
    }
    out << endl;

    return out;
}
