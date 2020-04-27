#ifndef BAG_H
#define BAG_H

#include <vector>
#include <string>
#include "Tile.h"
#include "Types.h"

class Bag
{
public:
    Bag();
    ~Bag();

    //Refill the bag from the discardedTiles vector, used when not enough tiles left to fill all factories
    void refillBag();

    //Grab a random tile from our bag
    Tile grabTile();


private:
    //Fixed size 1D Array for the tiles stored inside the bag
    Tile bag[MAX_TILES];

    //Dynamically sized vector for discarded tiles ("Box Lid")
    std::vector<Tile> discardedTiles;

    
};

#endif