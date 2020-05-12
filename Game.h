#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Table.h"
#include <iostream>

class Game
{
public:
    // Constructor for new game
    Game(std::string player1, std::string player2);
    // Constructor for loaded game (takes file input as parameter)
    Game(std::ifstream &fileInput);
    // Deconstructor
    ~Game();

    // Initialises new game
    void playGame();

    // Holds the logic for playing a round of the game
    void playRound();

    // Logic for an individual players turn
    void playerTurn();

    // Sets up the game for a new round
    void initialiseRound();

    // Check if the game end condition has been met (horizontal line completed)
    bool checkEnd();

    // Saves game at any time
    void saveGame();

    // Validate the input for a player turn, takes out a bulk of code from the round
    bool validateInput(int factory, char tile, int patternLine);



private:
    // Generic player pointers
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    // Pointer used to track current player
    Player* current;

    // Used to handle who has the first player token
    //Player* first;

    // Table ADT
    std::shared_ptr<Table> table;

    // Tracks current state of game - true if game has ended
    bool gameEnd;

    // Also need to add bag / lid

    const char tileColours[NUM_COLOURS] = {'R', 'Y', 'B', 'L', 'U'};
};

#endif //GAME_H