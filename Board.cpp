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
    // If the pattern line doesn't already has tiles in it
    //     If the pattern line isn't already complete
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

//if pattern line have no more space, and the pattern line is empty to start, move excess tiles to floor
//and fill the pattern line
int emptySlot = 0;
int overflow = 0;

//find how many tile slots are empty
    for(int i=0; i<2*patternLine; i++){
        if(patternLines[patternLine-1][MOSAIC_DIM-i]=='.'){
            emptySlot++;
        }
    }
//place the overflow tiles to floor
    if(tileCount>emptySlot){
        overflow=tileCount-emptySlot;
        placeInFloor(tileType, overflow);
    }

//place the tiles to pattern line
    int count=tileCount;
    for(int i=0; i<2*patternLine; ++i){
        if(patternLines[patternLine-1][MOSAIC_DIM-i]=='.' && count>0){
                patternLines[patternLine-1][MOSAIC_DIM-i]=tileType;
                --count;
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