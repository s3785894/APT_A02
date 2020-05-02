#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>

class Player
{
public:
    Player(std::string name);
    ~Player();

    std::string getName();
    
    int getScore();

private:
    Board *board;
    int score;

    std::string name;
};

#endif