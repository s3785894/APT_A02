#include "Bag.h"
#include <iostream>
#include <vector>

Bag::Bag()
{
    fillBag("", false);
}

Bag::Bag(std::string seed)
{
    fillBag(seed, true);
}

Bag::~Bag()
{
}

void Bag::viewContents()
{
}

void Bag::fillBag(std::string seed, bool isSeeded)
{
    //Fill the bag with our tiles, number of tiles per colour is determined by the max amount of tiles / the number of colours (even split)
    for (int i = 0; i < NUM_COLOURS; i++)
    {

        /*
            *   The for loop will loop as many times as there are different tiles
            *   
            *   The syntax for insert() is (position, amount, value)
            *   So what we have is (at end of our vector, insert an amount of tiles based on the calculation (20), insert the char at the index of the array that holds our possible tile colours)
            */
        bag.insert(bag.end(), (MAX_TILES / NUM_COLOURS), tileColours[i]);
    }

    // Print out bag before shuffling --- TESTING PURPOSES
    // for(int i = 0; i < bag.size(); i++){
    //     std::cout << bag[i];
    // }

    std::cout << "BAG CREATED" << std::endl;

    // std::cout << std::endl;

    //Once our bag is filled with our tiles, we need to shuffle it
    shuffleBag(seed, isSeeded);

    // Print out bag after shuffling --- TESTING PURPOSES
    // for(int i = 0; i < bag.size(); i++){
    //     std::cout << bag[i];
    // }
}

void Bag::refillBag()
{
    int size = discardedTiles.size();

    // Iterate through for the length of the Box-Lid, inserting our tiles from the Box-Lid into the i-th index of the bag, starting from the beginning.
    for (int i = 0; i < size; i++)
    {
        bag.insert(bag.begin() + i, discardedTiles[i]);
    }

    // Clear our Box-Lid
    discardedTiles.clear();

    // Shuffle the bag
    shuffleBag("", false);
}

void Bag::shuffleBag(std::string seed, bool isSeeded)
{
    int size = bag.size();
    //Set the seed based on the current system time to ensure a different seed every tme
    if (isSeeded)
    {
        srand(std::stoi(seed));
    }
    else
    {
        srand(time(0));
    }

    //Loops through each element of the vector
    for (int i = 0; i < size - 1; i++)
    {
        //Generate a random number, j, in the range of our vector size
        int j = i + rand() % (size - i);

        //Swap the tile at index j with the tile at the current index i
        std::swap(bag[i], bag[j]);
    }
}

char Bag::grabTile()
{
    // Each time a tile is grabbed, checked if the bag is empty, and if so, refill and shuffle the bag first
    if(bag.size() == 0){
        refillBag();
    }
    //Since our bag is always randomly shuffled at the start, to grab random tiles we can grab tiles from the front of the bag
    char tile = bag.front();

    //Remove this tile from the bag (Erase the first tile in the vector, which is the tile we've grabbed)
    bag.erase(bag.begin());

    //Return our tile
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

void Bag::placeInLid(const std::string& tiles){

    // Iterate through our string of discarded tiles, adding each tile to the back of our box lid one-by-one
    for(int i = 0; i < tiles.size(); i++){
        char tile = tiles[i];
        discardedTiles.push_back(tile);
    }
    
}