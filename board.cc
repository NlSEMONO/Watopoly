#include "board.h"
#include "academic.h"
#include "residence.h"
#include "dice.h"
#include <iostream>

Board::Board(): squares{}, nameToIndex{}, monopolies{}, players{}, currentPlayer{0}, dice{} {
    // hardcoding all buildings
    // OSAP
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts1", "AL", 40, 50, 0, {2, 10, 30, 90, 160, 250}}});
    // SLC
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts1", "ML", 60, 50, 0, {4, 20, 60, 180, 320, 450}}});
    // TUITION
    // RESIDENCE [MKV]
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "ECH", 100, 50, 0, {6, 30, 90, 270, 400, 550}}});
    // NEEDLES
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "PAS", 100, 50, 0, {6, 30, 90, 270, 400, 550}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Arts2", "HH", 120, 50, 0, {8, 40, 100, 300, 450, 600}}});
    // DC Tims Line
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "RCH", 140, 100, 0, {10, 50, 150, 450, 625, 750}}});
    // GYM [PAC]
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "DWE", 140, 100, 0, {10, 50, 150, 450, 625, 750}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Eng", "CPH", 160, 100, 0, {12, 60, 180, 500, 700, 900}}});
    // RESIDENCE [UWP]
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "LHI", 180, 100, 0, {14, 70, 200, 550, 750, 950}}});
    // SLC
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "BMH", 180, 100, 0, {14, 70, 200, 550, 750, 950}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Health", "OPT", 200, 100, 0, {16, 80, 220, 600, 800, 1000}}});
    // GOOSE NESTING
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV1", 220, 150, 0, {18, 90, 250, 700, 875, 1050}}});
    // NEEDLES
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV2", 220, 150, 0, {18, 90, 250, 700, 875, 1050}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Env", "EV3", 240, 150, 0, {20, 100, 300, 750, 925, 1100}}});
    // RESIDENCE [V1]
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "PHYS", 260, 150, 0, {22, 110, 330, 800, 975, 1150}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "B1", 260, 150, 0, {22, 110, 330, 800, 975, 1150}}});
    // GYM [CIF]
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci1", "B2", 280, 150, 0, {24, 120, 360, 850, 1025, 1200}}});
    // GOTOTIMS
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "EIT", 300, 200, 0, {26, 130, 390, 900, 1100, 1275}}});
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "ESC", 300, 200, 0, {26, 130, 390, 900, 1100, 1275}}});
    // SLC
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Sci2", "C2", 320, 200, 0, {28, 150, 450, 1000, 1200, 1400}}});
    // RESIDENCE [REV]
    // NEEDLES
    squares.push_back(std::unique_ptr<Academic>{new Academic{"Math", "MC", 350, 200, 0, {35, 175, 500, 1100, 1300, 1500}}});
    // COOP FEE
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
