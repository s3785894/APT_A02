#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    this->board = new Board();
    this->score = 0;
}

Player::Player(std::vector<std::string> loadedPlayer1)
{
    // Load player name and score, and check score validity (must be above zero)
    std::string playerName = loadedPlayer1.at(0);
    int score = std::stoi(loadedPlayer1.at(2));
    if (score < 0)
    {
        // throw error
    }

    // Get subvectors representing boad attributes and pass them into Board constructor
    std::vector<std::string> patternLines;
    for (int i = 3; i < 8; i++)
    {
        patternLines.at(i - 3) = loadedPlayer1.at(i);
    }
    std::vector<std::string> mosaicLines;
    for (int i = 8; i < 13; i++)
    {
        mosaicLines.at(i - 8) = loadedPlayer1.at(i);
    }
    std::string tileLineString = loadedPlayer1.at(13);

    board = new Board(patternLines, mosaicLines, tileLineString);
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