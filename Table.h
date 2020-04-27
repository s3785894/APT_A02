#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include "Player.h"
#include "Types.h"

class Table
{
public:
    Table();
    ~Table();

    // method used by players to draw from factory
    void draw(int factory, char tileType, Player &player);
    // initialises factories at start of each round
    void initialiseRound();
    // checks if any tiles are left in factories (to determine end of round)
    bool tilesLeft();
    // returns contents of factory as formatted string
    std::string printFactoryContents();

private:
    // stores tiles of factory zero (which can contain greater than four tiles)
    std::vector<char> factory_zero;
    // stores standard factories
    char factories[NUM_FACTORIES][FACTORY_SIZE];
};

#endif