#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Table.h"
#include "Bag.h"
#include <iostream>
#include <fstream>

class Game
{
public:
    // Constructor for new game
    Game(std::string playerOneName, std::string playerTwoName, std::string seed, bool hasSeeded);

    // Constructor for loaded game (takes file input as parameter)
    Game(std::ifstream &fileInput);

    // Deconstructor
    ~Game();

    // Initialises new game and controls the over all game loop
    void playGame(bool isMidRound);

    // Holds the logic for playing a round of the game
    void playRound();

    // Logic for an individual players turn
    void playerTurn();

    // Sets up the game for a new round
    void initialiseRound();

    // Check if the game end condition has been met (horizontal line completed)
    bool checkEnd();

    // Saves game at any time
    void saveGame(std::string fileName);

    // At round end, resolve the player boards and score the round
    void scoreRound();

    // At round end, clear the player boards of any pattern lines that are full, and all tiles on the floor, placing them in to the box lid
    void clearBoards();

    // Loads game from file
    void loadGame(std::ifstream &fileInput);

    // Complete the end game scoring and determine the winner
    void scoreGame();

    // Validate the input for a player turn, takes out a bulk of code from the round function
    bool validateInput(int factory, char tile, int patternLine);

private:
    // Generic player pointers
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    // Pointer used to track current player
    Player *current;

    // Tracks who the first player for next round is
    Player* firstPlayer;

    // Table ADT
    std::shared_ptr<Table> table;

    // Tracks current state of game - true if game has ended
    bool gameEnd;

    const char tileColours[NUM_COLOURS] = {'R', 'Y', 'B', 'L', 'U'};
};

#endif //GAME_H