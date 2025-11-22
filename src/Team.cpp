#include "Team.h"

Team::Team(const std::string &n)
    : name(n), totalRuns(0), wicketsLost(0), ballsPlayed(0) {}

void Team::resetInnings() {
    totalRuns = 0;
    wicketsLost = 0;
    ballsPlayed = 0;
    for (auto &p : players) {
        p.resetStats();
    }
}

int Team::getOversCompleted() const {
    return ballsPlayed / 6;
}

int Team::getBallsInCurrentOver() const {
    return ballsPlayed % 6;
}
