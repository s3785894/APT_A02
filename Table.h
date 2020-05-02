#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include "Player.h"
#include "Types.h"
#include "Bag.h"

class Table
{
public:
    Table();
    ~Table();

    // Grab tiles from chosen factory 
    void grabTiles(int factory, char tileColour, Player &player);

    // Initialises factories at start of each round
    void initialiseRound();

    // Checks if any tiles are left in factories (to determine end of round)
    bool tilesLeft();

    // Returns contents of factory as formatted string
    std::string printFactoryContents();

private:
    // Stores tiles in the 'table' centre. Dynamically sized as tiles will be continually added throughout the game
    std::vector<char> tableCentre;

    // Stores standard factories
    Factories factories;
};

#endif