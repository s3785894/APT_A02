#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
}

Player::~Player()
{
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    //score = board->calculateScore;
    //return score;
}

Board Player::getBoard()
{
    // Since Board is stored as a pointer, maybe we should have the function return a pointer?
    return *(this->board);
}

std::string Player::toString()
{
    // gets player info (name, score) and board information for use in saving
}