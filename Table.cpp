#include "Table.h"
#include <iostream>
#include <sstream>

Table::Table()
{
    bag = new Bag();
}

Table::Table(std::string seed)
{
    bag = new Bag(seed);
}

Table::Table(std::vector<std::string> tableLines)
{
    char tile;

    // Processes tables
    std::stringstream tableCentreStream(tableLines.at(0));
    while (tableCentreStream >> tile)
    {
        tableCentre.push_back(tile);
    }

    // Processes factories
    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        std::stringstream factoryStream(tableLines.at(i + 1));
        int colNum = 0;
        while (factoryStream >> tile)
        {
            factories[i][colNum] = tile;
            colNum++;
        }
    }

    bag = new Bag(tableLines.at(6), tableLines.at(7));
}

Table::~Table()
{
    delete bag;
}

int Table::takeTiles(int factory, char tileColour)
{
    /* 
    * 'Grab' tiles from chosen factory
    * 
    * What this function actually does is take in the parameters of which factory and which tile, and then it will count the number of that tile type within the given factory.
    * It will then return an int which represents the amount of tiles the player has taken, which is then used to place that amount of the chosen tile on to the player's board.
    * 
    * The idea is that we avoid passing around char values or tile objects, we instead just tell different components of our program how many tiles to place/remove from certain containers.
    * 
    * The remaining tiles from a factory will be transferred to the table centre (unless the player took from the table centre), and all the elements of the factory will be set to \0 (null char) to indicate that it is empty
    */

    int tileFrequency = 0;

    // If taking from factory 0, iterate through our tableCentre vector
    if (factory == 0)
    {
        std::vector<char>::iterator it = tableCentre.begin();

        // Iterate through our vector
        for (it = tableCentre.begin(); it != tableCentre.end();)
        {
            // Check if the tile at the current position matches the chosen tile colour
            if (tableCentre.at(it - tableCentre.begin()) == tileColour)
            {
                // If so, remove it and increase the tile count
                it = tableCentre.erase(it);
                tileFrequency++;
            }
            else
            {
                // If not, increase the iterator
                it++;
            }
        }
    }

    // Otherwise, if factory is not 0 we are taking from our 2D array
    else
    {
        // Iterate through the array
        for (int i = 0; i < FACTORY_SIZE; i++)
        {

            // For the given factory (which is our row), check if the element at the current position i matches the chosen tile colour
            // If it does, increase the tile frequency
            if (factories[factory - 1][i] == tileColour)
            {
                tileFrequency++;
            }
            else
            {
                // For any tiles that are not of the chosen colour, add these to the tableCentre
                tableCentre.push_back(factories[factory - 1][i]);
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

    // Starts true by default because of the logic of our checking
    bool factoryEmpty = true;

    // We first need to iterate through and check if our 2D array is empty since there is no simple function of doing this like with our vector
    // Loop through our factories array
    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        for (int j = 0; j < FACTORY_SIZE; j++)
        {
            // For each element, check if the element is null
            if (factories[i][j] != '\0')
            {
                // If at any point, there is an element that is not null, this means at least one factory is not empty and so factoryEmpty is set to false
                factoryEmpty = false;
            }
        }
    }

    // If our table centre is empty, and our 2D factories array has all elements as null, then we can say there are no tiles left on the table
    if (tableCentre.empty() && factoryEmpty)
    {
        tilesLeft = false;
    }

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

bool Table::checkFactory(int factory, char tileColour)
{
    bool validMove = false;

    // If taking from factory 0, iterate through our tableCentre vector
    if (factory == 0)
    {
        for (std::vector<char>::iterator i = tableCentre.begin(); i != tableCentre.end(); ++i)
        {
            // Check if tableCentre contains the chosen colour, if not, validMove will remain false
            if (*i == tileColour)
            {
                validMove = true;
            }
        }
    }

    // Otherwise, if factory is not 0 we are checking our 2D array
    else
    {
        // Iterate through the array
        for (int i = 0; i < FACTORY_SIZE; i++)
        {

            // For the given factory (which is our row), check if the element at the current position i matches the chosen tile colour
            // If it does, the move is valid.
            if (factories[factory - 1][i] == tileColour)
            {
                validMove = true;
            }
        }
    }

    // If no tiles of the chosen colour were found, print out a simple message to let the user know what was wrong (in addition to the 'Invalid Input' message)
    if (!validMove)
    {
        std::cout << "Sorry, there is no tile of that colour to be taken!" << std::endl;
    }

    return validMove;
}

bool Table::checkFirstPlayerToken()
{
    // The first player token will always be the first index of the table centre, therefore, we just need to check index 0 instead of looping through the whole vector

    bool tokenExists;

    if (tableCentre.size() > 0)
    {
        tokenExists = tableCentre.at(0) == 'F';

        // If the token is on the table, we must also remove it since it will be moved to the player board
        if (tokenExists)
        {
            tableCentre.erase(tableCentre.begin());
        }
    }
    else
    {
        tokenExists = false;
    }

    // Return whether or not the token is on the table. If true, the game handles the logic of giving this token to the player
    return tokenExists;
}

void Table::placeInLid(const std::string &tiles)
{
    bag->placeInLid(tiles);
}

std::string Table::toString()
{
    std::string details = "";
    // Factory 0 (Table Center)
    for (int i = 0; i < tableCentre.size(); i++)
    {
        details += tableCentre.at(i);
        if (!(i == tableCentre.size() - 1))
        {
            details += " ";
        }
    }
    details += "\n";
    // Factories
    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        for (int j = 0; j < FACTORY_SIZE; j++)
        {
            details += factories[i][j];
            if (!(j == FACTORY_SIZE - 1))
            {
                details += " ";
            }
        }
        details += "\n";
    }
    details += bag->toString();
    return details;
}