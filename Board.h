#ifndef BOARD_H
#define BOARD_H

#include "Types.h"

#include <iostream>

#include "LinkedList.h"

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

    // Prints the whole player board
    void prntBoard();

    //Prints the floor tile
    void printFloor();

    //Clear floor
    void clearFloor();

    // Check if the chosen tile is able to be placed in the chosen pattern line (Meaning the pattern line doesn't already contain another colour or the chosen colour isn't already placed in that row on the mosaic)
    bool checkBoard(int patternLine, char tileType);

private:
    Mosaic mosaic;

    Mosaic patternLines;

    LinkedList* floorTile;
};

#endif //BOARD_H