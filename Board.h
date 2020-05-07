#ifndef BOARD_H
#define BOARD_H

#include "Types.h"

#include <iostream>

class Board
{
public:
    // Constructor for new board
    Board();
    // Constructor for loaded board
    Board(Mosaic mosaic);
    // Deconstructor
    ~Board();

    // Insert collection of tiles into specific pattern line
    void placeInPatternLine(int patternLine, char tileType, int tileCount);
    // Insert leftover tiles in floor line
    void placeInFloor(char tileType, int tileCount);

    // Move from pattern lines to mosaic
    void patternLineToMosaic();

    // Prints mosaic
    void prntMosaic();

private:
    Mosaic mosaic;
    // pattern lines
    // tile line
};

#endif //BOARD_H