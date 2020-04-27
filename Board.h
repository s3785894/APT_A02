#ifndef BOARD_H
#define BOARD_H

#include "Types.h"

typedef char Mosaic[MOSAIC_DIM][MOSAIC_DIM];

class Board
{
public:
    Board();
    ~Board();

    // insert collection of tiles into pattern line
    void placeInPatternLine(int patternLine, char tileType, int tileCount);
    // move from pattern lines to mosaic
    void patternLineToMosaic();

private:
    Mosaic mosaic;
    // pattern lines
    // tile line
};

#endif //BOARD_H