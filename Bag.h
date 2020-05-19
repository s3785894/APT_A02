#ifndef BAG_H
#define BAG_H

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include "Types.h"

class Bag
{
public:
    // Constructor for new games
    Bag();
    // Constructor for new games w/ seeded order
    Bag(std::string seed);
    // Constructor for loaded games
    Bag(std::string tileBagString, std::string tileLidString);
    // Deconstructor
    ~Bag();

    // Fill the bag with out initial amount of tiles (game start)
    void fillBag(std::string seed, bool isSeeded);

    // Refill the bag from our discarded tiles. Generally this will be the same as fill bag but if more factories are ever used this is needed
    void refillBag();

    // Shuffle the bag randomly
    void shuffleBag(std::string seed, bool isSeeded);

    // Grab a tile from our bag
    char grabTile();

    // For testing, not sure if would ever be needed in the actual game
    void viewContents();

    // Place the discarded tiles from a bag in to the box lid
    void placeInLid(const std::string &tiles);

    // Check if the bag is empty
    bool isEmpty();

    //
    std::string toString();

private:
    // Dynamically sized vector for tiles in play
    std::vector<char> bag;

    // Dynamically sized vector for discarded tiles ("Box Lid")
    std::vector<char> discardedTiles;

    // 1D array of chars, indicating our tiles
    const char tileColours[NUM_COLOURS] = {'R', 'Y', 'B', 'L', 'U'};
};

#endif