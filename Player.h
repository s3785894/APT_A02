#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player
{
public:
    Player();
    ~Player();

private:
    Board *board;
    int score;
};

#endif