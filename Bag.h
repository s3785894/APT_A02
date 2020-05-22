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
    // Default constructor for the bag, uses a random seed to shuffle
    Bag();

    // Constructor for bag with a given seed. Allows the user to determine a fixed shuffle order (mainly for testing)
    Bag(std::string seed);

    // Fill the bag and box-lid vectors based on given strings. Used when loading in a state from a save file
    Bag(std::string tileBagString, std::string tileLidString);

    // Deconstructor
    ~Bag();

    // Fill the bag with our initial amount of tiles (game start). If provided a seed, the shuffle order will be fixed based on the seed
    void fillBag(std::string seed, bool isSeeded);

    // Refill the bag from our discarded tiles. Used when the bag becomes empty mid game
    void refillBag();

    // Shuffle the bag based on the give seed. If no seed is given, the seed is based on the user system clock and will provide a random shuffle
    void shuffleBag(std::string seed, bool isSeeded);

    // Grab a tile from our bag
    char grabTile();

    // Place the discarded tiles from a round in to our box-lid
    void placeInLid(const std::string &tiles);

    // Check if the bag is empty
    bool isEmpty();

    // Output the contents of the bag as a singular string, used to store the bag state when saving
    std::string toString();

private:
    // Dynamically sized vector for tiles in play
    std::vector<char> bag;

    // Dynamically sized vector for discarded tiles ("Box Lid")
    std::vector<char> discardedTiles;

    // 1D array of chars, indicating our possible tile colours
    const char tileColours[NUM_COLOURS] = {'R', 'Y', 'B', 'L', 'U'};
};

#endif