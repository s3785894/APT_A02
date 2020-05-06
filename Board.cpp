#include "Board.h"

Board::Board()
{
    this->mosaic = new Mosaic();
}

Board::Board(Mosaic mosaic)
{
    this->mosaic = mosaic;
}

Board::~Board()
{
    // deallocate appropriate factors
}

void Board::placeInPatternLine(int patternLine, char tileType, int tileCount)
{
    // If the pattern line doesn't already has tiles in it
    //     If the pattern line isn't already complete complete
    //         Place tiles in line
    //         If overflow occurs
    //             Place overflowed tiles in floor
    //         Endif
    //     Else
    //         Throw error?
    //     Endif
    // Else
    //     Throw error?
    // Endif
}

void Board::patternLineToMosaic(Player &player)
{
    // For all pattern lines (top to bottom, or small to large)
    //     If pattern line is complete
    //         If a free space on that line is open on the mosaic
    //             Fill that mosaic space
    //             Place the amount of tiles on that line MINUS ONE in the lid
    //         Else
    //             Probably don't throw error?
    //         Endif
    //      Else
    //         Probably don't throw error?
    // Endfor
    //
    // Possibly calculate and update Player score here?
}

void Board::placeInFloor(char tileType, int tileCount)
{
    // Iterate over tile line, adding identical char 'tileType' tileCount times
}

Mosaic Board::getMosaic()
{
    return this->mosaic;
}