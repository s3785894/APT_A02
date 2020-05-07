#include "Table.h"
#include <iostream>

Table::Table()
{
    bag = new Bag();
}

Table::~Table()
{
    delete bag;
}

void Table::takeTiles(int factory, char tileColour, Player &player)
{
    // Should we check to see if the move is valid? Should we delegate that to another function?

    // For factory picked
    //   Iterate over entire factory
    //   Log how many times the character showed up
    //   Set each instance of the character to a filler value, such as null or nullptr

    int tileFrequency = 0;
    if (factory == 0)
    {
        // do it fot the vector
    }
    else
    {
        for (int i = 0; i < FACTORY_SIZE; i++)
        {
            if (this->factories[0][i] == tileColour)
            {
                tileFrequency++;
                // set current position to a filler value to signify none left (e.g. null, nullptr)
            }
        }
    }

    // may need to intergrate this with other logic or change return type - it needs to be inserted in specific line on player board
}

void Table::initialiseRound()
{
    // Put the first player token in the table centre
    tableCentre.insert(tableCentre.begin(), 'F');

    // Fill our factories from our bag of tiles
    for (int factory = 0; factory < NUM_FACTORIES; factory++)
    {
        for (int column = 0; column < FACTORY_SIZE; column++)
        {
            factories[factory][column] = bag->grabTile();
        }
    }
}

bool Table::tilesLeft()
{
    bool tilesLeft = true;

    /*
    * if (tableCentre.empty() || (iterate  through factory array and check if tiles are there)) {
    *   tilesLeft = false;
    * } else {
    *   tilesLeft = true;
    * }
    */

    return tilesLeft;
}

void Table::printFactoryContents()
{
    std::cout << "Factories:" << std::endl;

    // First print our table centre as 'factory 0'
    std::cout << "0: ";
    for (int i = 0; i < tableCentre.size(); i++)
    {
        std::cout << tableCentre.at(i) << " ";
    }

    std::cout << std::endl;

    // Then print our array containing our tile factories
    for (int factory = 0; factory < NUM_FACTORIES; factory++)
    {
        std::cout << factory + 1 << ": ";

        // Iterate through the current factory and print each element, seperated by a space
        for (int column = 0; column < FACTORY_SIZE; column++)
        {
            std::cout << factories[factory][column] << " ";
        }

        // Go to next line after all tiles in a factory are printed
        std::cout << std::endl;
    }

    std::cout << std::endl;
}