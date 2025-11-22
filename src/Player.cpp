#include "Player.h"

Player::Player(const std::string &n, const std::string &r)
    : name(n), role(r) {
    resetStats();
}

void Player::resetStats() {
    runs = 0;
    ballsFaced = 0;
    fours = 0;
    sixes = 0;
    isOut = false;
    wickets = 0;
    ballsBowled = 0;
    runsConceded = 0;
}
