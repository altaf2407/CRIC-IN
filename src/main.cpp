#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "Player.h"
#include "Team.h"

using namespace std;

// -------------------- UTILITY: CLEAR INPUT BUFFER --------------------
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// -------------------- RANDOM BALL OUTCOME --------------------
/*
   Returns:
   -1  -> Wicket
   0   -> Dot ball
   1,2,3,4,6 -> runs
*/
int getRandomBallOutcome() {
    int r = rand() % 100; // 0-99

    if (r < 25) return 0;          // 25% dot
    else if (r < 55) return 1;     // 30% single
    else if (r < 70) return 2;     // 15% double
    else if (r < 80) return 3;     // 10% three
    else if (r < 92) return 4;     // 12% four
    else if (r < 97) return 6;     // 5% six
    else return -1;                // 3% wicket
}

// -------------------- SCOREBOARD DISPLAY --------------------
void showScoreboard(const Team &battingTeam) {
    cout << "\n------------------------------\n";
    cout << "Scoreboard - " << battingTeam.name << "\n";
    cout << "Score: " << battingTeam.totalRuns << "/" << battingTeam.wicketsLost
         << " in " << battingTeam.getOversCompleted() << "." << battingTeam.getBallsInCurrentOver()
         << " overs\n";
    cout << "------------------------------\n";
    cout << "Player\t\tRuns(Balls)\t4s\t6s\tStatus\n";
    for (const auto &p : battingTeam.players) {
        cout << p.name << "\t\t"
             << p.runs << "(" << p.ballsFaced << ")\t"
             << p.fours << "\t" << p.sixes << "\t"
             << (p.isOut ? "OUT" : "NOT OUT") << "\n";
    }
    cout << "------------------------------\n\n";
}

// -------------------- INNINGS SIMULATION --------------------
void playInnings(Team &battingTeam, Team &bowlingTeam, int oversPerInnings, int target = -1) {
    battingTeam.resetInnings();

    cout << "\n----------------------------------------\n";
    cout << "Innings Starts: " << battingTeam.name << " Batting\n";
    cout << "----------------------------------------\n";

    int numPlayers = static_cast<int>(battingTeam.players.size());
    if (numPlayers < 2) {
        cout << "Not enough players to play innings!\n";
        return;
    }

    int strikerIndex = 0;
    int nonStrikerIndex = 1;
    int nextBatsmanIndex = 2;

    bool inningsOver = false;

    for (int over = 0; over < oversPerInnings && !inningsOver; ++over) {
        cout << "\nOver " << (over + 1) << " begins...\n";
        for (int ball = 0; ball < 6; ++ball) {
            if (battingTeam.wicketsLost == numPlayers - 1) {
                cout << "All out!\n";
                inningsOver = true;
                break;
            }

            if (target != -1 && battingTeam.totalRuns > target) {
                inningsOver = true;
                break;
            }

            Player &striker = battingTeam.players[strikerIndex];

            int outcome = getRandomBallOutcome();

            battingTeam.ballsPlayed++;

            cout << "Ball " << (over + 1) << "." << (ball + 1) << " - ";

            if (outcome == -1) {
                striker.isOut = true;
                battingTeam.wicketsLost++;
                cout << striker.name << " is OUT!\n";

                if (nextBatsmanIndex < numPlayers) {
                    strikerIndex = nextBatsmanIndex;
                    nextBatsmanIndex++;
                } else {
                    cout << "No batsman left. Innings ends.\n";
                    inningsOver = true;
                    break;
                }
            } else {
                striker.runs += outcome;
                striker.ballsFaced++;

                if (outcome == 4) striker.fours++;
                if (outcome == 6) striker.sixes++;

                battingTeam.totalRuns += outcome;

                if (outcome == 0) {
                    cout << "Dot ball.\n";
                } else if (outcome == 4) {
                    cout << "FOUR by " << striker.name << "!\n";
                } else if (outcome == 6) {
                    cout << "SIX! Huge hit by " << striker.name << "!\n";
                } else {
                    cout << striker.name << " scores " << outcome << " run(s).\n";
                }

                // Strike rotation for 1 or 3 runs
                if (outcome == 1 || outcome == 3) {
                    int temp = strikerIndex;
                    strikerIndex = nonStrikerIndex;
                    nonStrikerIndex = temp;
                }
            }

            showScoreboard(battingTeam);

            if (target != -1 && battingTeam.totalRuns > target) {
                cout << battingTeam.name << " has chased down the target!\n";
                inningsOver = true;
                break;
            }
        }

        // Over complete and innings not over -> rotate strike
        if (!inningsOver) {
            int temp = strikerIndex;
            strikerIndex = nonStrikerIndex;
            nonStrikerIndex = temp;
        }
    }

    cout << "\nInnings over! Final Score for " << battingTeam.name << ": "
         << battingTeam.totalRuns << "/" << battingTeam.wicketsLost << " in "
         << battingTeam.getOversCompleted() << "." << battingTeam.getBallsInCurrentOver()
         << " overs.\n";

    showScoreboard(battingTeam);
}

// -------------------- FIND TOP SCORER --------------------
Player getTopScorer(const Team &team) {
    Player top = team.players[0];
    for (const auto &p : team.players) {
        if (p.runs > top.runs) {
            top = p;
        }
    }
    return top;
}

// -------------------- MAIN FUNCTION --------------------
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "=============================================\n";
    cout << "        CRIC-IN : VIRTUAL CRICKET GAME       \n";
    cout << "                (C++ Project)                \n";
    cout << "=============================================\n\n";

    // --------- Team Setup ----------
    string teamAName, teamBName;
    int numPlayers, oversPerInnings;

    cout << "Enter Team A name: ";
    cin >> teamAName;
    cout << "Enter Team B name: ";
    cin >> teamBName;

    Team teamA(teamAName);
    Team teamB(teamBName);

    cout << "\nEnter number of players per team (min 2, max 11 recommended): ";
    cin >> numPlayers;
    if (numPlayers < 2) numPlayers = 2;

    cout << "Enter number of overs per innings (e.g., 2, 5, 10): ";
    cin >> oversPerInnings;
    if (oversPerInnings < 1) oversPerInnings = 2;

    cout << "\n--- Enter details for " << teamA.name << " ---\n";
    for (int i = 0; i < numPlayers; ++i) {
        string pname, prole;
        cout << "Player " << (i + 1) << " name: ";
        cin >> pname;
        cout << "Role (Batsman/Bowler/All-rounder/WK): ";
        cin >> prole;
        teamA.players.push_back(Player(pname, prole));
    }

    cout << "\n--- Enter details for " << teamB.name << " ---\n";
    for (int i = 0; i < numPlayers; ++i) {
        string pname, prole;
        cout << "Player " << (i + 1) << " name: ";
        cin >> pname;
        cout << "Role (Batsman/Bowler/All-rounder/WK): ";
        cin >> prole;
        teamB.players.push_back(Player(pname, prole));
    }

    // --------- Toss ----------
    cout << "\n----------------------------------------\n";
    cout << "               TOSS TIME                 \n";
    cout << "----------------------------------------\n";
    cout << "Call the toss " << teamA.name << " (0 for HEADS, 1 for TAILS): ";
    int call;
    cin >> call;
    int toss = rand() % 2;

    bool teamAWonToss = (call == toss);

    cout << "Coin result: " << (toss == 0 ? "HEADS" : "TAILS") << "\n";
    if (teamAWonToss) {
        cout << teamA.name << " won the toss!\n";
    } else {
        cout << teamB.name << " won the toss!\n";
    }

    int choice; // 1 - bat, 2 - bowl
    if (teamAWonToss) {
        cout << teamA.name << ", choose: 1 for BAT, 2 for BOWL: ";
        cin >> choice;
    } else {
        cout << teamB.name << ", choose: 1 for BAT, 2 for BOWL: ";
        cin >> choice;
    }

    Team *firstBattingTeam;
    Team *secondBattingTeam;

    if (teamAWonToss) {
        if (choice == 1) {
            firstBattingTeam = &teamA;
            secondBattingTeam = &teamB;
            cout << teamA.name << " will BAT first.\n";
        } else {
            firstBattingTeam = &teamB;
            secondBattingTeam = &teamA;
            cout << teamA.name << " will BOWL first. " << teamB.name << " will BAT.\n";
        }
    } else {
        if (choice == 1) {
            firstBattingTeam = &teamB;
            secondBattingTeam = &teamA;
            cout << teamB.name << " will BAT first.\n";
        } else {
            firstBattingTeam = &teamA;
            secondBattingTeam = &teamB;
            cout << teamB.name << " will BOWL first. " << teamA.name << " will BAT.\n";
        }
    }

    // --------- First Innings ----------
    playInnings(*firstBattingTeam, *secondBattingTeam, oversPerInnings);

    int target = firstBattingTeam->totalRuns;
    cout << "\nTarget for " << secondBattingTeam->name << " is: "
         << target + 1 << " runs.\n";

    // --------- Second Innings ----------
    playInnings(*secondBattingTeam, *firstBattingTeam, oversPerInnings, target);

    // --------- Result ----------
    cout << "\n=============================================\n";
    cout << "                 MATCH RESULT                \n";
    cout << "=============================================\n";

    cout << firstBattingTeam->name << " scored: " << firstBattingTeam->totalRuns
         << "/" << firstBattingTeam->wicketsLost << "\n";
    cout << secondBattingTeam->name << " scored: " << secondBattingTeam->totalRuns
         << "/" << secondBattingTeam->wicketsLost << "\n";

    if (firstBattingTeam->totalRuns > secondBattingTeam->totalRuns) {
        cout << "\n" << firstBattingTeam->name << " WON the match by "
             << (firstBattingTeam->totalRuns - secondBattingTeam->totalRuns) << " runs!\n";
    } else if (secondBattingTeam->totalRuns > firstBattingTeam->totalRuns) {
        int wicketsRemaining = static_cast<int>(secondBattingTeam->players.size()) - secondBattingTeam->wicketsLost;
        cout << "\n" << secondBattingTeam->name << " WON the match by "
             << wicketsRemaining << " wickets!\n";
    } else {
        cout << "\nThe match is a TIE!\n";
    }

    // Top scorers
    Player top1 = getTopScorer(*firstBattingTeam);
    Player top2 = getTopScorer(*secondBattingTeam);

    cout << "\nTop Scorer for " << firstBattingTeam->name << ": "
         << top1.name << " - " << top1.runs << " runs.\n";
    cout << "Top Scorer for " << secondBattingTeam->name << ": "
         << top2.name << " - " << top2.runs << " runs.\n";

    cout << "\nThank you for playing CRIC-IN!\n";

    return 0;
}
