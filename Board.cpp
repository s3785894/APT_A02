#include "Board.h"
#include <memory>

#define floorSize 7

Board::Board()
{
    // Initialise our Mosaic to default values
    for(int i = 0; i < MOSAIC_DIM; i++){
        for(int j = 0; j < MOSAIC_DIM; j++){
            mosaic[i][j] = '.';
        }
    }

    // Initialise our Pattern Lines to default values
    // The spaces in the pattern line that are available to have a tile in them are represented by a '.' whilst the rest of the row is filled with ' ' 
    for(int i = 0; i < MOSAIC_DIM; i++){
        for(int j = 0; j < MOSAIC_DIM; j++){
            if(j + 1 >= MOSAIC_DIM - i){
                patternLines[i][j] = '.';
            } else {
                patternLines[i][j] = ' ';
            }
        }
    }

    //intialise floor
    floorTile = new LinkedList();

}

Board::Board(Mosaic mosaic)
{
    for(int i = 0; i < MOSAIC_DIM; i++){
        for(int j = 0; j < MOSAIC_DIM; j++){
            this->mosaic[i][j] = mosaic[i][j];
        }
    }
}

Board::~Board()
{
    // deallocate appropriate factors
}

void Board::placeInPatternLine(int patternLine, char tileType, int tileCount)
{
    // To place the tiles in the pattern line, we need to check how many spaces are empty in that pattern line, and then place tiles to the pattern line or the floor appopriately
    int emptySlot = 0;
    int overflow = 0;
    
    // Find how many tile slots are empty
        for(int i = 0; i < patternLine; i++){
            if(patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i]=='.'){
                emptySlot++;
            }
        }

    // Place the overflow tiles to floor
        if(tileCount > emptySlot){
            overflow  = tileCount - emptySlot;
            placeInFloor(tileType, overflow);
        }

    // Find our starting index place the tiles (skip over tiles already in the pattern line)
    int startIndex = (MOSAIC_DIM - 1) - (patternLine - emptySlot);
    // Place the tiles to pattern line
        for(int i = 0; i < tileCount; i++){
            if(emptySlot > 0){
                    patternLines[patternLine-1][startIndex - i] = tileType;
                    --emptySlot;
            }
        }
    
}

int Board::patternLineToMosaic(int patternLine)
{
    // Given the pattern line we're in (row);
    // Check the tile colour on the pattern line patterLine[patterLine][MOSAIC_DIM - 1]
    // Iterate through that row on our Mosaic Colours array to find where the tile goes [i][j]
    // On our Mosaic, at positon [i][j] place a tile of that colour

    // Get the color of the tile we're placing
    char tile = patternLines[patternLine][MOSAIC_DIM - 1];

    int position;
    int score = 0;

    // Find the position of the colour on the mosaic in the given row
    for(int i = 0; i < MOSAIC_DIM; i++){
        if(mosaicColours[patternLine][i] == tile){
            position = i;
        }
    }

    // Place our tile in the give positon on the mosaic
    mosaic[patternLine][position] = tile;

    // Clear the pattern line
    for(int i = 0; i < patternLine; i ++){
        patternLines[patternLine][(MOSAIC_DIM - 1) - i] = '.';
    }

    // Execute logic for scoring
    if(mosaic[patternLine]) {

    }

    return score;
}

void Board::placeInFloor(char tileType, int tileCount)
{
    // Iterate over tile line, adding identical char 'tileType' tileCount times
    for(int i=0; i<tileCount; ++i){
        floorTile->addBack(tileType);
    }
}

// I think this function  is not needed anymore?
void Board::prntMosaic()
{
    for(int i = 0; i < MOSAIC_DIM; i++){
        for(int j = 0; j < MOSAIC_DIM; j++){
            std::cout << mosaic[i][j];
        }
        std::cout << std::endl;
    }
}

void Board::printFloor(){
        std::cout<<"broken: ";

        for(int i=0; i<floorTile->size(); ++i){
            std::cout<<floorTile->get(i)<<" ";
        }

}

void Board::prntBoard()
{
    // To print the whole board for the player, we need to print both the pattern lines and mosaic line by line at the same time

    for(int row = 0; row < MOSAIC_DIM; row++){
        std::cout << row + 1 << ": ";

        for(int col = 0; col < MOSAIC_DIM; col++){
            std::cout << patternLines[row][col];
            std::cout << " ";
        }

        std::cout << "|| ";

        for(int col = 0; col < MOSAIC_DIM; col++){
            std::cout << mosaic[row][col];
            std::cout << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    // Print out the floor tiles (Negative Score)
    printFloor();
    //TO DO Add floor

    std::cout << std::endl;
}


void Board::clearFloor(){
    floorTile->clear();
}

bool Board::checkBoard(int patternLine, char tileType)
{
    bool validMove = true;
    bool empty = false; 
    // Check that the chosen pattern line does not contain another tile colour
    // Check that the mosaic in the same row does not already contain a tile of the chosen colour
    // If both checks pass, then return true (valid move)

    // Check that the chosen pattern line contains ONLY either empty spaces OR tiles of the chosen colour, if not, validMove is false. Also ensures there is at least one empty space in the pattern line
    for(int i = 0; i < patternLine; i++){
        if(patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != tileType){
            if(patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != '.'){
                validMove = false;
            } else {
                empty = true;
            }
        }
    }

    if(!empty){
        validMove = false;
    }

    // Check that the mosaic in the chosen row does not contain a tile of the chosen colour, if it does, validMove is false
    for(int i = 0; i < MOSAIC_DIM; i++){
        if(mosaic[patternLine - 1][(MOSAIC_DIM - 1) - i] == tileType){
            validMove = false;
        }
    }

    // If either of 1 of these conditions are met, the move cannot be made by the player and they must re-enter their input. Print a meaningful message for the player
    if(!empty){
        std::cout << "The chosen pattern line is full!" << std::endl;
    } else if (!validMove){
        std::cout << "The chosen pattern line contains tiles of another colour, or that row already has a tile of that colour on the mosaic." << std::endl;
    }

    return validMove;
}

int Board::resolveBoard(){
    // Initialise our column int to the back of our pattern line
    int column = MOSAIC_DIM - 1;

    int score = 0;

    // Starting from line one iterate through the pattern lines checking they are full
    for(int i = 0; i < MOSAIC_DIM; i++){
        // Initialise a boolean full to default value true, indicating the line is full
        bool full = true;

        // Check if the starting element on the pattern line is empty, if it is we don't need to bother checking the whole line
        if(patternLines[i][column] != '.'){
            for(int j = 0; j < i + i; j++){
                // For each index of the pattern line, check if there is an empty space character. If so, the pattern line is not full, otherwise full will remain true
                if(patternLines[i][j] == '.'){
                    full = false;
                }
            }

            // After the whole line has been checked, if full is still true it means our pattern line is full and a tile should be moved to the mosaic
            std::cout << "LINE " << i << " IS " << full << std::endl;

            if(full){
               score = score + patternLineToMosaic(i);
            }
        }

    }

    return score;
}
