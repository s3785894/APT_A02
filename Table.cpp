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

int Table::takeTiles(int factory, char tileColour)
{
    int tileFrequency = 0;

    // If taking from factory 0, iterate through our tableCentre vector
    if (factory == 0)
    {
        for (std::vector<char>::iterator i = tableCentre.begin() ; i != tableCentre.end(); ++i){
            // For each tile found matching the chosen colour, increase tile frequency and then erase that tile from the vector
            if(*i == tileColour){
                tileFrequency++;
                tableCentre.erase(i);
            }
        }
    }

    // Otherwise, if factory is not 0 we are taking from our 2D array 
    else
    {
        // Iterate through the array
        for(int i = 0; i < FACTORY_SIZE; i++){

            // For the given factory (which is our row), check if the element at the current position i matches the chosen tile colour
            // If it does, increase the tile frequency
            if(factories[factory - 1][i] == tileColour){
                tileFrequency++;
            }

            // Since we always remove all tiles from the factory, all of the chosen factories elements will be set to null
            factories[factory - 1][i] = '\0';
        }
    }

    // Return the frequency count back to the game
    return tileFrequency;
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