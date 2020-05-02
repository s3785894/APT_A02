#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Table.h"
#include <iostream>

class Game
{
public:
    Game(std::string player1, std::string player2);
    ~Game();

    // Initialises new game
    void playGame();

    // Loads new game from file
    void playGame(std::ifstream &fileInput);

    // Holds the logic for playing a round of the game
    void playRound();

    // Check if the game end condition has been met (horizontal line completed)
    void checkEnd();

private:
    Player* player1;
    Player* player2;
    Table* table;
    
    bool gameEnd;
};

#endif //GAME_H