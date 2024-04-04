#include "board_graphics.h"
#include "academic.h"
using namespace std;

BoardGraphics::BoardGraphics(): w{}, block_to_colour{} {
    block_to_colour["Arts1"] = Colour::Brown;
    block_to_colour["Arts2"] = Colour::LightBlue;
    block_to_colour["Eng"] = Colour::Pink;
    block_to_colour["Health"] = Colour::Orange;
    block_to_colour["Env"] = Colour::Red;
    block_to_colour["Sci1"] = Colour::Yellow;
    block_to_colour["Sci2"] = Colour::Green;
    block_to_colour["Math"] = Colour::Blue;
}

pair<int, int> BoardGraphics::indexToCoords(int index) const {
    if (20 <= index && index <= 30) return make_pair((index - 20) * tile_width, 0);
    else if (index >= 30) return make_pair(10 * tile_width, (index - 30) * tile_height);
    else if (10 <= index && index <= 20) return make_pair(0, (20 - index) * tile_height);
    return make_pair((index - 20) * tile_width, 10 * tile_height);
}

void BoardGraphics::drawTiles(Board& b) {
    for (int i = 0; i < NUM_SQUARES; ++i) {
        Square* curr = b.getSquare(i);
        pair<int, int> location = indexToCoords(i);
        w.fillRectangle(location.first, location.second, tile_width, tile_height);
        if (b.isAcademic(i)) {
            Academic* acaPtr = dynamic_cast<Academic*>(curr);
            w.drawString(location.first + NAME_OFFSET, location.second + IMPROVEMENT_OFFSET, curr->getName());
            w.fillRectangle(location.first, location.second, tile_width, IMPROVEMENT_OFFSET, block_to_colour[]);
        }
        else w.drawString(location.first + NAME_OFFSET, location.second, curr->getName());
    }
}

void BoardGraphics::printPlayers(int tile_index) {
    
}

void board
