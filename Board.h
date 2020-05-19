#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include "LinkedList.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

class Board
{
public:
    // Constructor for new board
    Board();
    // Constructor for loaded board
    Board(std::vector<std::string> patternLines, std::vector<std::string> mosaicLines, std::string tileLineString);
    // Deconstructor
    ~Board();

    // Insert collection of tiles into specific pattern line
    void placeInPatternLine(int patternLine, char tileType, int tileCount);
    // Insert leftover tiles in floor line
    void placeInFloor(char tileType, int tileCount);

    // Move from pattern lines to mosaic. Scores the tile when moved, returns an int with the score gained
    int patternLineToMosaic(int patternLine);

    // Prints mosaic
    void prntMosaic();

    // Prints the whole player board
    void prntBoard();

    //Prints the floor tile
    void printFloor();

    //Clear floor
    void clearFloor();

    // Check for end game condition
    bool isRowFilled();

    // Clear board of the floor tiles and any pattern lines that are full. Return a string of the tiles cleared so that these can be placed in the box lid
    std::string clearBoard();

    // After making the necessary moves, an int will be returned which represents the players earned score for that round
    int resolveBoard();

    // Check if the chosen tile is able to be placed in the chosen pattern line (Meaning the pattern line doesn't already contain another colour or the chosen colour isn't already placed in that row on the mosaic)
    bool checkBoard(int patternLine, char tileType);

    int scoreBonus();

    int floorSlot();

    char removeLastFloorTile();

    std::string toString();

private:
    Mosaic mosaic;

    Mosaic patternLines;

    LinkedList *floorTile;

    Mosaic mosaicColours =
        {
            {'B', 'Y', 'R', 'U', 'L'},
            {'L', 'B', 'Y', 'R', 'U'},
            {'U', 'L', 'B', 'Y', 'R'},
            {'R', 'U', 'L', 'B', 'Y'},
            {'Y', 'R', 'U', 'L', 'B'}};

    int floorScore[7] = {1, 1, 2, 2, 2, 3, 3};

    // Holds our endgame condition. Storing in a bool allows us to simply check the value of the boolean in the game loop, instead of constantly needing to iterate through our array each time
    bool rowFilled;
};

#endif //BOARD_H