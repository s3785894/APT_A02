#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    board = new Board();
    score = 0;
}

Player::Player(std::vector<std::string> loadedPlayer1)
{
    name = loadedPlayer1.at(0);
    score = std::stoi(loadedPlayer1.at(2));
    // Throws an exception if the score is below zero (impossible state)
    if (score < 0)
    {
        throw std::exception();
    }

    // Passes subvectors (and string) representing board data to the board
    std::vector<std::string> patternLines;
    for (int i = 3; i < 8; i++)
    {
        patternLines.push_back(loadedPlayer1.at(i));
    }

    std::vector<std::string> mosaicLines;
    for (int i = 8; i < 13; i++)
    {
        mosaicLines.push_back(loadedPlayer1.at(i));
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

int Player::countRows()
{
    return board->countRows();
}

bool Player::isRowFilled()
{
    return board->isRowFilled();
}

void Player::addScore(int roundScore)
{
    // Roundscore can possibly be a negative int so we need to check if the total score becomes less than 0. If so, set score to 0 as a player cannot have a negative total score
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

char Player::removeFromFloor()
{
    return board->removeLastFloorTile();
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

int Player::hasFloorSlot(){
    return board->floorSlot();
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
