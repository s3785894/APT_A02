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

    /*
    std::string playerName = fileLines.at(8);
    std::string currentPlayerAsString = fileLines.at(9);
    if (currentPlayerAsString == "True" || currentPlayerAsString == "False")
    {
        if (currentPlayerAsString == "True")
        {
            isPlayerOneCurrent = true;
        }
    }
    else
    {
        throw;
    }
    int score = std::stoi(fileLines.at(9));
    // BOARD PROCESSING
    Board *board;
    */
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
    if (score + roundScore < 0)
    {
        score = 0;
    }
    else
    {
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

void Player::endRound()
{
    //board->patternLineToMosaic();
    board->clearFloor();
}

bool Player::checkBoard(int patternLine, char tileType)
{
    return board->checkBoard(patternLine, tileType);
}

void Player::placeInFloor(char tileType, int tileCount)
{
    board->placeInFloor(tileType, tileCount);
}

void Player::resolveBoard()
{
    int roundScore = board->resolveBoard();
    addScore(roundScore);

    std::cout << name << "'s score for the round: " << roundScore << std::endl;
}

std::string Player::clearBoard()
{
    std::string tilesCleared = board->clearBoard();
    return tilesCleared;
}

std::string Player::toString(bool isCurrent)
{
    return name + "\n" + (isCurrent ? "True" : "False") + "\n" + std::to_string(score) + board->toString();
}

void Player::scoreBonus()
{
    int scoreBonus = board->scoreBonus();

    addScore(scoreBonus);
}