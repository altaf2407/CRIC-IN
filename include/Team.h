#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include "Player.h"

class Team {
public:
    std::string name;
    std::vector<Player> players;
    int totalRuns;
    int wicketsLost;
    int ballsPlayed;

    Team(const std::string &n = "");

    void resetInnings();

    int getOversCompleted() const;
    int getBallsInCurrentOver() const;
};

#endif // TEAM_H
