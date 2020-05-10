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

void Player::prntBoard()
{
    std::cout << "Board for Player: " << name << std::endl;
    board->prntBoard();
    std::cout << std::endl;
}

void Player::placeTiles(int patternLine, char tileType, int tileCount)
{
    board->placeInPatternLine(patternLine, tileType, tileCount);
}

void Player::endRound(){
    board->patternLineToMosaic();
    board->clearFloor();
}



std::string Player::toString()
{
    // gets player info (name, score) and board information for use in saving

    // Placeholder return statement
    return name;
}