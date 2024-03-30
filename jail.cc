#include "jail.h"

Jail::Jail(): Square{"DC Tims Line"} {}

Jail::~Jail() {}

// void Jail::sendToJail(Player* player) {
//     jailedTurns[player] = 0;
// }

// bool Jail::handleMove(Player* player) {
//     if (jailedTurns[player] == 3) {
//         removePlayer(player);
//         return true;
//     }
//     ++jailedTurns[player];
//     return false;
// }
