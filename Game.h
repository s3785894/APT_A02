#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Table.h"

class Game
{
public:
    Game();
    ~Game();

    // initialises new game
    void playGame();
    // loads new game from file
    void playGame(std::ifstream &fileInput);

private:
    Player *player1;
    Player *player2;
    Table *table;
    // deck?
};

#endif //GAME_H