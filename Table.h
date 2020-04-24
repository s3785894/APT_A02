#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "Player.h"

class Table
{
public:
    Table();
    ~Table();

    // method used by players to draw from factory
    void draw(int factory, char tileType, &Player player);
    // initialises factories at start of each round
    void initialiseRound();
    // checks if any tiles are left in factories (to determine end of round)
    bool tilesLeft();

private:
    std::vector<char> factory_zero;
    char factories[5][4];
}

#endif