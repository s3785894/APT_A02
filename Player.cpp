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

bool Player::isRowFilled()
{
    return board->isRowFilled();
}


void Player::addScore(int roundScore)
{
    if(score + roundScore < 0){
        score = 0;
    } else {
        score = score + roundScore;
    }
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
    //board->patternLineToMosaic();
    board->clearFloor();
}

bool Player::checkBoard(int patternLine, char tileType){
    return board->checkBoard(patternLine, tileType);
}

void Player::placeInFloor(char tileType, int tileCount){
    board->placeInFloor(tileType, tileCount);
}

void Player::resolveBoard(){
    int roundScore = board->resolveBoard();
    addScore(roundScore);

    std::cout << name <<"'s score for the round: " << roundScore << std::endl;
}

std::string Player::clearBoard(){
    std::string tilesCleared = board->clearBoard();
    return tilesCleared;
}



std::string Player::toString()
{
    // gets player info (name, score) and board information for use in saving

    // Placeholder return statement
    return name;
}

void Player::scoreBonus(){
    int scoreBonus = board->scoreBonus();

    addScore(scoreBonus);
}