#include "board_graphics.h"
#include <sstream>
#include "academic.h"
using namespace std;

BoardGraphics::BoardGraphics(): w{width, height}, block_to_colour{} {
    block_to_colour["Arts1"] = Colour::Brown;
    block_to_colour["Arts2"] = Colour::LightBlue;
    block_to_colour["Eng"] = Colour::Pink;
    block_to_colour["Health"] = Colour::Orange;
    block_to_colour["Env"] = Colour::Red;
    block_to_colour["Sci1"] = Colour::Yellow;
    block_to_colour["Sci2"] = Colour::Green;
    block_to_colour["Math"] = Colour::Blue;
}

BoardGraphics::~BoardGraphics(){
    b = nullptr;
}

pair<int, int> BoardGraphics::indexToCoords(int index) const {
    if (20 <= index && index <= 30) return make_pair((index - 20) * tile_width, 0);
    else if (index >= 30) return make_pair(10 * tile_width, (index - 30) * tile_height);
    else if (10 <= index && index <= 20) return make_pair(0, (20 - index) * tile_height);
    return make_pair((10 - index) * tile_width, 10 * tile_height);
}

void BoardGraphics::drawTiles(Board& b) {
    w.fillRectangle(0, 0, width, height, Colour::White);
    for (int i = 0; i < NUM_SQUARES; ++i) {
        Square* curr = b.getSquare(i);
        pair<int, int> location = indexToCoords(i);
        w.fillRectangle(location.first, location.second, 1, tile_height);
        w.fillRectangle(location.first + tile_width, location.second, 1, tile_height);
        w.fillRectangle(location.first, location.second, tile_width, 1);
        w.fillRectangle(location.first, location.second + tile_height, tile_width, 1);
        if (b.isAcademic(i)) {
            Academic* acaPtr = dynamic_cast<Academic*>(curr);
            w.drawString(location.first + NAME_OFFSET, location.second + FONT_OFFSET + IMPROVEMENT_OFFSET, curr->getName());
            w.fillRectangle(location.first, location.second, tile_width, IMPROVEMENT_OFFSET, block_to_colour[acaPtr->getBlock()]);
        }
        else {
            istringstream iss{curr->getName()};
            string data;
            int offset_counter = 1;
            bool removeNH = b.isNeedles(i);
            bool removeSLC = b.isSLC(i);
            while (iss >> data) {
                w.drawString(location.first + NAME_OFFSET, location.second + (offset_counter * FONT_OFFSET), 
                    (removeNH && offset_counter == 2) ? data.substr(0, data.size() - 1) : 
                    (removeSLC && offset_counter) ? data.substr(0, data.size() - 1) : data);
                ++offset_counter;
            }
        } 
        string players = curr->printPlayers();
        string to_print = "";
        int j = 0;
        while (players[j] != ' ' && players[j] != '|') {
            to_print += string(1, players[j]);
            ++j;
        }
        w.drawString(location.first + NAME_OFFSET, location.second + PLAYER_OFFSET, to_print);
    }
}


void BoardGraphics::printImprovements(Board &b) {
    for (int i = 0; i < 40; ++i) {
        if (b.isAcademic(i)) {
            Academic *cur = dynamic_cast<Academic *> (b.getSquare(i));
            int upgradeLevel = cur->getUpgradeLevel();
            std::pair<int, int> coords = indexToCoords(i);
            int x = coords.first;
            int y = coords.second;
            for (int j = 0; j < upgradeLevel; ++j) {
                w.fillRectangle(x + 12 *j, y + 1,8 ,8, Colour::Black);
            }
        }
    }
}

ostream &operator<<(ostream &out, BoardGraphics &bg) {
    bg.drawTiles(*bg.b);
    bg.printImprovements(*bg.b);
    return out;
}


void BoardGraphics::setBoard(Board* board) { b = board;}
