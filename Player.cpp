#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    this->board = new Board();
    this->score = 0;
}

Player::Player(std::string name, Board *board, int score)
{
    this->name = name;
    this->board = board;
    this->score = score;
}

Player::~Player()
{
    delete board;
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
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