#include "board_graphics.h"
using namespace std;

pair<int, int> boardGraphics::indexToCoords(int index) const {
    if (20 <= index && index <= 30) return make_pair((index - 20) * tile_width, 0);
    else if (index >= 30) return make_pair(10 * tile_width, (index - 30) * tile_height);
    else if (10 <= index && index <= 20) return make_pair(0, (20 - index) * tile_height);
    return make_pair((index - 20) * tile_width, 10 * tile_height);
}

void boardGraphics::drawTiles(Board& b) {
    for (int i = 0; i < NUM_SQUARES; ++i) {
        Square* curr = b.getSquare(i);
        pair<int, int> location = indexToCoords(i);
        w.fillRectangle(location.first, location.second, tile_width, tile_height);
        if (b.isAcademic(i)) {
            w.drawString(location.first + NAME_OFFSET, location.second + IMPROVEMENT_OFFSET, curr->getName());
            w.fillRectangle(location.first, location.second, tile_width, IMPROVEMENT_OFFSET, );
        }
        else w.drawString(location.first + NAME_OFFSET, location.second, curr->getName());
    }
}

void boardGraphics::printPlayers(int tile_index) {

}