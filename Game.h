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

    // Check if the game end condition has been met (horizontal line completed)
    void checkEnd();

    // Saves game at any time
    void saveGame();

private:
    // Generic player pointers
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    // Pointer used to track current player
    Player *current;
    // Table ADT
    Table *table;
    // Tracks current state of game - true if game has ended
    bool gameEnd;

    // Also need to add bag / lid
};

#endif //GAME_H