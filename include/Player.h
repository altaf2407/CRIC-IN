#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    std::string name;
    std::string role;         // Batsman / Bowler / All-rounder / WK
    int runs;
    int ballsFaced;
    int fours;
    int sixes;
    bool isOut;

    // Bowling stats (optional basic)
    int wickets;
    int ballsBowled;
    int runsConceded;

    Player(const std::string &n = "", const std::string &r = "Batsman");

    void resetStats();
};

#endif // PLAYER_H
