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

    // Insert excess tiles in floor line
    void placeInFloor(char tileType, int tileCount);
    
    // 'Resolves' the player board at the end of a round, using the patternLineToMosaic() function to move tiles. Returns the players score for that round
    int resolveBoard();

    // Moves a tile from a full pattern line on to the mosaic at round end. Calculates score for that tile and then returns an int with the score gained from the move
    int patternLineToMosaic(int patternLine);

    // Prints the pattern lines, mosaic, and floor in a formatted structure to show the entire player board
    void prntBoard();

    // Clears the floor of all tiles
    void clearFloor();

    // Check for end game condition
    bool isRowFilled();

    // Clear board of the floor tiles and any pattern lines that are full. Return a string of the tiles cleared so that these can be placed in the box lid
    std::string clearBoard();

    // Check if the chosen tile is able to be placed in the chosen pattern line (Meaning the pattern line doesn't already contain another colour or the chosen colour isn't already placed in that row on the mosaic)
    bool checkBoard(int patternLine, char tileType);

    // Calculates the end of game score bonuses
    int scoreBonus();

    // Counts the number of rows filled at the end of the game. Only used if the game end scoring results in a tie
    int countRows();

    int floorSlot();

    // Removes the last tile in the floor and places it in the box lid. This function is used in the rare scenario that the first player is taken by a player that already has a full floor. 
    // The game will switch out the last floor tile and replace it with the First Player Token.
    char removeLastFloorTile();

    // Returns the current state of the board as a string for use in a save game file
    std::string toString();

    int getHLineCount();

private:
    // 5x5 array for the player board mosaic
    Mosaic mosaic;

    // 5x5 array for the player board pattern lines
    Mosaic patternLines;

    // Linked list for the player board floor
    LinkedList *floorTile;

    // 2D array with the hard-coded structure of where the tile colours go in the mosaic
    Mosaic mosaicColours =
        {
            {'B', 'Y', 'R', 'U', 'L'},
            {'L', 'B', 'Y', 'R', 'U'},
            {'U', 'L', 'B', 'Y', 'R'},
            {'R', 'U', 'L', 'B', 'Y'},
            {'Y', 'R', 'U', 'L', 'B'}};

    // Stores the points values for the position of tiles in the floor
    int floorScore[7] = {1, 1, 2, 2, 2, 3, 3};

    // Holds our endgame condition. Storing in a bool allows us to simply check the value of the boolean in the game loop, instead of constantly needing to iterate through our array each time
    bool rowFilled;
};

#endif //BOARD_H