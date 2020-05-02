#ifndef BOARD_H
#define BOARD_H

#include "Types.h"

class Board
{
public:
    Board();
    ~Board();

    // insert collection of tiles into pattern line
    void placeInPatternLine(int patternLine, char tileType, int tileCount);

    void placeInFloor(char tileType, int tileCount);

    // Move from pattern lines to mosaic
    void patternLineToMosaic();

private:
    Mosaic mosaic;
    // pattern lines
    // tile line
};

#endif //BOARD_H