#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>

class Player
{
public:
    // Constructor for new (not loaded) player
    Player(std::string name);
    // Constructor for loaded player
    Player(std::string name, Board *board, int score);
    // Deconstructor
    ~Player();

    // Returns name (for console output)
    std::string getName();
    // Returns current score
    int getScore();
    // Add a score from a round to the players total
    void addScore(int roundScore);

    // Check if end game condition is met
    bool isRowFilled();

    // Returns player's board
    void prntBoard();

    // Converts all attributes to string (for use in saving to file)
    std::string toString(bool isCurrent);

    // Call on the checkBoard function in board to check if player move is valid
    bool checkBoard(int patternLine, char tileType);

    //Player places tiles on pattern line
    void placeTiles(int patternLine, char tileType, int tileCount);

    void placeInFloor(char tileType, int tileCount);

    void resolveBoard();

    std::string clearBoard();

    void endRound();

    void scoreBonus();

private:
    // Pointer to player's board
    Board *board;
    // Player score
    int score;
    // Player name
    std::string name;
};

#endif