#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>
#include <vector>
#include <exception>

class Player
{
public:
    // Constructor for new (not loaded) player
    Player(std::string name);
    // Constructor for loaded player
    Player(std::vector<std::string> loadedPlayer1);
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
    // Calls checkboard function in board to check if player move is valid
    bool checkBoard(int patternLine, char tileType);
    // Places tiles on pattern line (called from game)
    void placeTiles(int patternLine, char tileType, int tileCount);
    // Places tiles in floor line
    void placeInFloor(char tileType, int tileCount);
    char removeFromFloor();
    // Resolves board
    void resolveBoard();
    // Clears board (for new board)
    std::string clearBoard();
    // Runs end of round clean-up
    void endRound();
    // Calculates bonus score
    void scoreBonus();

    int hasFloorSlot();

    // Counts the number of rows filled at the end of the game. Only used if the game end scoring results in a tie
    int countRows();

private:
    // Pointer to player's board
    Board *board;
    // Player score
    int score;
    // Player name
    std::string name;
};

#endif