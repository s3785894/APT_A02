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

    // Grab tiles from chosen factory (renamed to avoid confusion with getTiles method in bag)
    void takeTiles(int factory, char tileColour, Player &player);

    // Initialises factories at start of each round
    void initialiseRound();

    // Checks if any tiles are left in factories (to determine end of round)
    bool tilesLeft();

    // Prints contents of factory
    void printFactoryContents();

private:
    // Stores tiles in the 'table' centre. Dynamically sized as tiles will be continually added throughout the game
    std::vector<char> tableCentre;

    // Stores standard factories
    Factories factories;

    // Our bag of tiles is create through the table, this is because table is the only class that ever interacts with our bag of tiles
    Bag* bag;
};

#endif