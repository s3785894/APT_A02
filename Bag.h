#ifndef BAG_H
#define BAG_H

#include <vector>
#include <string>
#include "Types.h"

class Bag
{
public:
    Bag();
    ~Bag();

    //Refill the bag from the discardedTiles vector, used when not enough tiles left to fill all factories
    void refillBag();

    //Grab a random tile from our bag
    char grabTile();

    //For testing, not sure if would ever be needed in the actual game
    void viewContents();


private:
    //Dynamically sized vector for tiles in play
    std::vector<char> bag;

    //Dynamically sized vector for discarded tiles ("Box Lid")
    std::vector<char> discardedTiles;

    
};

#endif