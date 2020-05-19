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
    // Constructor for new games
    Table();
    // Constructor for new games (seeded)
    Table(std::string seed);
    // Constructor for loaded games
    Table(std::vector<std::string> tableLines);
    // Deconstructor
    ~Table();

    // Take tiles from a factory and indicate the number of tiles taken to place on the player board
    int takeTiles(int factory, char tileColour);

    // Initialises factories at start of each round
    void initialiseRound();

    // Checks if any tiles are left in factories (to determine end of round)
    bool tilesLeft();

    // Checks if the factory contains any tiles, and if it contains any tiles of the selected color (player turn validation)
    bool checkFactory(int factory, char tileColour);

    // Check if the table centre contains the first player token
    bool checkFirstPlayerToken();

    // Prints contents of factory
    void printFactoryContents();

    // Pass the tiles used in a round to the bag to be placed in to the box lid
    void placeInLid(const std::string &tiles);

    std::string toString();

private:
    // Stores tiles in the 'table' centre. Dynamically sized as tiles will be continually added throughout the game
    std::vector<char> tableCentre;

    // Stores standard factories
    Factories factories;

    // Our bag of tiles is create through the table, this is because table is the only class that ever interacts with our bag of tiles
    Bag *bag;
};

#endif