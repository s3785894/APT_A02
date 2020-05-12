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
    // Constructor for new gamees
    Table();
    // Constructor for loaded games
    Table(std::vector<char> tableCentre, Factories factories, Bag *bag);
    // Deconstructor
    ~Table();

    /* 
    * 'Grab' tiles from chosen factory (renamed to avoid confusion with getTiles method in bag)
    * 
    * What this function actually does is take in the parameters of which factory and which tile, and then it will count the number of that tile type within the given factory.
    * It will then return an int which represents the amount of tiles the player has taken, which is then used to place that amount of the chosen tile on to the player's board.
    * 
    * The idea is that we never actually pass around char values or tile objects, we instead just tell different components of our program how many tiles to place/remove from certain containers.
    * 
    * The remaining tiles from a factory will be transferred to the table centre (unless the player took from the table centre), and all the elements of the factory will be set to \0 (null char) to indicate that it is empty
    */ 
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

private:
    // Stores tiles in the 'table' centre. Dynamically sized as tiles will be continually added throughout the game
    std::vector<char> tableCentre;

    // Stores standard factories
    Factories factories;

    // Our bag of tiles is create through the table, this is because table is the only class that ever interacts with our bag of tiles
    Bag *bag;
};

#endif