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

void Board::patternLineToMosaic()
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
    // Check that the chosen pattern line does not contain another tile colour
    // Check that the mosaic in the same row does not already contain a tile of the chosen colour
    // If both checks pass, then return true (valid move)

    // Check that the chosen pattern line contains ONLY either empty spaces OR tiles of the chosen colour, if not, validMove is false
    for(int i = 0; i < patternLine; i++){
        if(patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != '.'){
            if(patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != tileType){
                validMove = false;
            }
        }
    }

    // Check that the mosaic in the chosen row does not contain a tile of the chosen colour, if it does, validMove is false
    for(int i = 0; i < MOSAIC_DIM; i++){
        if(mosaic[patternLine - 1][(MOSAIC_DIM - 1) - i] == tileType){
            validMove = false;
        }
    }

    // If either of 1 of these conditions are met, the move cannot be made by the player and they must re-enter their input. Print a meaningful message for the player
    if(!validMove){
        std::cout << "The chosen pattern line contains tiles of another colour, or that row already has a tile of that colour on the mosaic." << std::endl;
    }

    return validMove;
}
