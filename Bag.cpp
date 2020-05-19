#include "Bag.h"

Bag::Bag()
{
    fillBag("", false);
}

Bag::Bag(std::string seed)
{
    fillBag(seed, true);
}

Bag::Bag(std::string tileBagString, std::string tileLidString)
{
    char tile;

    // Processes string (line) from file into ordered tile bag
    std::stringstream tileBagStream(tileBagString);
    while (tileBagStream >> tile)
    {
        bag.push_back(tile);
    }
    // Processes string (line) from file into ordered tile bag
    std::stringstream tileLidStream(tileLidString);
    while (tileLidStream >> tile)
    {
        discardedTiles.push_back(tile);
    }
}

Bag::~Bag()
{
}

void Bag::fillBag(std::string seed, bool isSeeded)
{
    // Fill the bag with our tiles, number of tiles per colour is determined by the max amount of tiles / the number of colours (even split). With the current default rules being used, this means there are 20 of each tile.
    for (int i = 0; i < NUM_COLOURS; i++)
    {

        /*
            *   The for loop will loop as many times as there are different tiles
            *   
            *   The syntax for insert() is (position, amount, value)
            *   So what we have is (at end of our vector, insert an amount of tiles based on the calculation (20), insert the char at the current index of the array that holds our possible tile colours)
        */

        bag.insert(bag.end(), (MAX_TILES / NUM_COLOURS), tileColours[i]);
    }

    //Once our bag is filled with our tiles, we need to shuffle it. If a seed was provided at the beginning of the program, the seed is passed to the shuffle function
    shuffleBag(seed, isSeeded);
}

void Bag::refillBag()
{
    int size = discardedTiles.size();

    // Iterate through for the length of the Box-Lid, inserting our tiles from the Box-Lid into the i-th index of the bag, starting from the beginning.
    for (int i = 0; i < size; i++)
    {
        bag.insert(bag.begin() + i, discardedTiles[i]);
    }

    // Clear our Box-Lid as we've taken the tiles
    discardedTiles.clear();

    // Shuffle the bag
    shuffleBag("", false);
}

void Bag::shuffleBag(std::string seed, bool isSeeded)
{
    int size = bag.size();

    // If given a seed by the user, use this seed. 
    if (isSeeded)
    {
        srand(std::stoi(seed));
    }

    //Otherwise, use a seed based on the use system clock for a random shuffle
    else
    {
        srand(time(0));
    }

    // Loops through each element of the vector
    for (int i = 0; i < size - 1; i++)
    {
        // Generate a random number, j, based on our seed in the range of our vector size
        int j = i + rand() % (size - i);

        //Swap the tile at index j with the tile at the current index i
        std::swap(bag[i], bag[j]);
    }
}

char Bag::grabTile()
{
    // Each time we attempt to grab a tile, first check if the bag is empty, and if so, refill the bag from the box-lid and shuffle
    if (isEmpty())
    {
        refillBag();
    }

    //Since our bag is always randomly shuffled before we grab a tile, to grab a 'random' tile, we simply take the first tile in our vector
    char tile = bag.front();

    // Remove this tile from the bag
    bag.erase(bag.begin());

    // Return the tile that has been grabbed
    return tile;
}

bool Bag::isEmpty()
{
    bool isEmpty;

    if (bag.size() > 0)
    {
        isEmpty = false;
    }
    else
    {
        isEmpty = true;
    }

    return isEmpty;
}

void Bag::placeInLid(const std::string &tiles)
{
    // Iterate through our string of discarded tiles, adding each tile to the back of our box lid one-by-one
    for (int i = 0; i < tiles.size(); i++)
    {
        char tile = tiles[i];
        discardedTiles.push_back(tile);
    }
}

std::string Bag::toString()
{
    std::string details = "";
    
    // Tile Bag
    for (int i = 0; i < bag.size(); i++)
    {
        details += bag.at(i);
        if (!(i == bag.size() - 1))
        {
            details += " ";
        }
    }
    details += "\n";

    // Box Lid
    for (int i = 0; i < discardedTiles.size(); i++)
    {
        details += discardedTiles.at(i);
        if (!(i == discardedTiles.size() - 1))
        {
            details += " ";
        }
    }
    details += "\n";
    return details;
}