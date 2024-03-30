#include "board.h"
#include "academic.h"
#include "residence.h"
#include "dice.h"
#include "osap.h"
#include "slc.h"
#include "needleshall.h"
#include "tuition.h"
#include "jail.h"
#include "gym.h"
#include "coop.h"
#include "goosenest.h"
#include "gototims.h"
#include <iostream>
#include <string>

using namespace std;

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

Board::Board(): squares{}, nameToIndex{}, monopolies{} {
    const vector<int> residenceRents{25, 50, 100, 200};
    const int gymCost = 150;
    const int residenceCost = 200;
    // hardcoding all buildings

    squares.push_back(std::unique_ptr<OSAP>{new OSAP{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts1", "AL", 40, 50, 0, {2, 10, 30, 90, 160, 250}}});
    squares.push_back(std::unique_ptr<SLC>{new SLC{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts1", "ML", 60, 50, 0, {4, 20, 60, 180, 320, 450}}});
    squares.push_back(std::unique_ptr<Tuition>{new Tuition{}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"MKV", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "ECH", 100, 50, 0, {6, 30, 90, 270, 400, 550}}});
    squares.push_back(std::unique_ptr<NeedlesHall>{new NeedlesHall{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "PAS", 100, 50, 0, {6, 30, 90, 270, 400, 550}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "HH", 120, 50, 0, {8, 40, 100, 300, 450, 600}}});
    squares.push_back(std::unique_ptr<Jail>{new Jail{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "RCH", 140, 100, 0, {10, 50, 150, 450, 625, 750}}});
    squares.push_back(std::unique_ptr<Gym>{new Gym{"PAC", gymCost}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "DWE", 140, 100, 0, {10, 50, 150, 450, 625, 750}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "CPH", 160, 100, 0, {12, 60, 180, 500, 700, 900}}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"UWP", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "LHI", 180, 100, 0, {14, 70, 200, 550, 750, 950}}});
    squares.push_back(std::unique_ptr<SLC>{new SLC{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "BMH", 180, 100, 0, {14, 70, 200, 550, 750, 950}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "OPT", 200, 100, 0, {16, 80, 220, 600, 800, 1000}}});
    squares.push_back(std::unique_ptr<GooseNest>{new GooseNest{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV1", 220, 150, 0, {18, 90, 250, 700, 875, 1050}}});
    squares.push_back(std::unique_ptr<NeedlesHall>{new NeedlesHall{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV2", 220, 150, 0, {18, 90, 250, 700, 875, 1050}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV3", 240, 150, 0, {20, 100, 300, 750, 925, 1100}}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"V1", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "PHYS", 260, 150, 0, {22, 110, 330, 800, 975, 1150}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "B1", 260, 150, 0, {22, 110, 330, 800, 975, 1150}}});
    squares.push_back(std::unique_ptr<Gym>{new Gym{"CIF", gymCost}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "B2", 280, 150, 0, {24, 120, 360, 850, 1025, 1200}}});
    squares.push_back(std::unique_ptr<GoToTims>{new GoToTims{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "EIT", 300, 200, 0, {26, 130, 390, 900, 1100, 1275}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "ESC", 300, 200, 0, {26, 130, 390, 900, 1100, 1275}}});
    squares.push_back(std::unique_ptr<SLC>{new SLC{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "C2", 320, 200, 0, {28, 150, 450, 1000, 1200, 1400}}});
    squares.push_back(std::unique_ptr<Residence>{new Residence{"REV", residenceCost, residenceRents}});
    squares.push_back(std::unique_ptr<NeedlesHall>{new NeedlesHall{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Math", "MC", 350, 200, 0, {35, 175, 500, 1100, 1300, 1500}}});
    squares.push_back(std::unique_ptr<Coop>{new Coop{}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Math", "DC", 400, 200, 0, {50, 200, 600, 1400, 1700, 2000}}});

    // store names to relevant index in a map (so we don't have to loop during game execution)
    int count = 0;
    for (auto& it : squares) {
        nameToIndex[it.get()->getName()] = count;
        ++count;
    }

    // map monopoly names to relevant properties
    monopolies["Arts1"] = {1, 3}; 
    monopolies["Arts2"] = {6, 8, 9};
    monopolies["Eng"] = {11, 13, 14};
    monopolies["Health"] = {16, 18, 19};
    monopolies["Env"] = {21, 23, 24};
    monopolies["Sci1"] = {26, 28, 29};
    monopolies["Sci2"] = {31, 32, 34};
    monopolies["Math"] = {37, 39};
    monopolies["Residence"] = {5, 15, 25, 35};
    monopolies["Gyms"] = {12, 28};
    monopolies["SLC"] = {2, 17, 33};
    monopolies["Needles"] = {7, 22, 36};
}

// int Board::rollDice(){
//     Dice Dice1;
//     Dice Dice2;
//     Event e1 = Dice1.generateEvent();
//     Event e2 = Dice2.generateEvent();
//     int roll1 = Dice1.eventToInt(e1);
//     int roll2 = Dice1.eventToInt(e2);
//     return roll1 + roll2;
// }

// void Board::makeMove(Player *p) {
//     int diceRoll = rollDice();
//     p->movePlayer(diceRoll);
// }

// void Board::addPlayer(std::string name) {
//     players.push_back(std::unique_ptr<Player>{new Player{name, 0, 0, 0, 0}});
//     currentPlayer++;
// }

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

bool Board::isType(string type, int buildingCode) {
    if (monopolies.count(type) == 0) return false;
    vector<int>& toSearch = monopolies[type];

    return find(toSearch.begin(), toSearch.end(), buildingCode) != toSearch.end();
}

void Board::initBuilding(std::string name, Player* owner, int upgrades) {
    if (nameToIndex.count(name) == 0) return;
    int buildingCode = nameToIndex[name];

    if (isType("Residence", buildingCode)) {
        Residence& toChange = dynamic_cast<Residence&>(*squares[buildingCode].get());
        toChange.setOwner(owner);
        if (upgrades == -1) toChange.setMortgaged();
    } else if (isType("Gyms", buildingCode)) {
        Gym& toChange = dynamic_cast<Gym&>(*squares[buildingCode].get());
        toChange.setOwner(owner);
        if (upgrades == -1) toChange.setMortgaged();
    } else if (isType("Arts1", buildingCode) || isType("Arts2", buildingCode) || isType("Eng", buildingCode) || 
            isType("Health", buildingCode) || isType("Env", buildingCode) || isType("Sci1", buildingCode) || 
            isType("Sci2", buildingCode) || isType("Math", buildingCode)) {
        Academic& toChange = dynamic_cast<Academic&>(*squares[buildingCode].get());
        toChange.setOwner(owner);
        if (upgrades > -1) toChange.setUpgrades(upgrades);
        else toChange.setMortgaged();
    }
}
