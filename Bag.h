#ifndef BAG_H
#define BAG_H

#include <vector>
#include <algorithm>
#include <string>
#include "Types.h"

class Bag
{
public:
    Bag();
    ~Bag();

    //Fill the bag
    void fillBag();

    //Shuffle the bag randomly 
    void shuffleBag();

    //Grab a tile from our bag
    char grabTile();

    //For testing, not sure if would ever be needed in the actual game
    void viewContents();


private:
    //Dynamically sized vector for tiles in play
    std::vector<char> bag;

    //Dynamically sized vector for discarded tiles ("Box Lid")
    std::vector<char> discardedTiles;

    //1D array of chars, indicating our tiles
    const char tileColours[NUM_COLOURS] = {'R', 'Y', 'B', 'L', 'U'};
    
};

#endif