#include "Board.h"
#include <memory>

#define floorSize 7

Board::Board()
{
    // Initialise our Mosaic to default values
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            mosaic[i][j] = '.';
        }
    }

    // Initialise our Pattern Lines to default values
    // The spaces in the pattern line that are available to have a tile in them are represented by a '.' whilst the rest of the row is filled with ' '
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            if (j + 1 >= MOSAIC_DIM - i)
            {
                patternLines[i][j] = '.';
            }
            else
            {
                patternLines[i][j] = ' ';
            }
        }
    }

    //intialise floor
    floorTile = new LinkedList();

    rowFilled = false;
}

Board::Board(Mosaic mosaic)
{
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
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
    for (int i = 0; i < patternLine; i++)
    {
        if (patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] == '.')
        {
            emptySlot++;
        }
    }

    // Place the overflow tiles to floor
    if (tileCount > emptySlot)
    {
        overflow = tileCount - emptySlot;
        placeInFloor(tileType, overflow);
    }

    // Find our starting index place the tiles (skip over tiles already in the pattern line)
    int startIndex = (MOSAIC_DIM - 1) - (patternLine - emptySlot);
    // Place the tiles to pattern line
    for (int i = 0; i < tileCount; i++)
    {
        if (emptySlot > 0)
        {
            patternLines[patternLine - 1][startIndex - i] = tileType;
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

    // Find the position of the colour on the mosaic in the given row
    int position;
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        if (mosaicColours[patternLine][i] == tile)
        {
            position = i;
        }
    }

    // Place our tile in the give positon on the mosaic
    mosaic[patternLine][position] = tile;

    // EXECUTE LOGIC FOR SCORING

    int score = 0;

    bool adjacentLeft = true;
    bool adjacentRight = true;
    bool adjacentUp = true;
    bool adjacentDown = true;

    // Check adjacent tiles to the left, if not, score for the amount in the row going left
    if (position == 0 || mosaic[patternLine][position - 1] == '.')
    {
        adjacentLeft = false;
    }
    else
    {
        int curPos = position;
        // Iterate through our mosaic moving down. The loop will continue until an empty space or the edge of the mosaic is reached
        while (mosaic[patternLine][curPos] != '.' && curPos >= 0)
        {
            score++;
            curPos--;
        }
    }

    // Check adjacent tiles to the right, if not, score for the amount in the row going right
    if (position == 4 || mosaic[patternLine][position + 1] == '.')
    {
        adjacentRight = false;
    }
    else
    {
        int curPos = position;
        // If there are adjacent tiles to the left it means we have already counted our current tile in the scoring, which means we need to remove a point so the tile is not counted twice for the same row
        if (adjacentLeft)
        {
            score--;
        }
        // Iterate through our mosaic moving down. The loop will continue until an empty space or the edge of the mosaic is reached
        while (mosaic[patternLine][curPos] != '.' && curPos < MOSAIC_DIM)
        {
            score++;
            curPos++;
        }
    }

    // Check adjacent tiles above, if not, score for the amount in the column going up
    if (patternLine == 0 || mosaic[patternLine - 1][position] == '.')
    {
        adjacentUp = false;
    }
    else
    {
        int curRow = patternLine;
        // Iterate through our mosaic moving down. The loop will continue until an empty space or the edge of the mosaic is reached
        while (mosaic[curRow][position] != '.' && curRow >= 0)
        {
            score++;
            curRow--;
        }
    }

    // Check adjacent tiles below, if not, score for the amount in the column going down
    if (patternLine == 4 || mosaic[patternLine + 1][position] == '.')
    {
        adjacentDown = false;
    }
    else
    {
        int curRow = patternLine;
        // If there are adjacent tiles above it means we have already counted our current tile in the scoring, which means we need to remove a point so the tile is not counted twice for the same column
        if (adjacentUp)
        {
            score--;
        }
        // Iterate through our mosaic moving down. The loop will continue until an empty space or the edge of the mosaic is reached
        while (mosaic[curRow][position] != '.' && curRow < MOSAIC_DIM)
        {
            score++;
            curRow++;
        }
    }

    // If our tile has no adjacent tiles, the score is just one
    if (!adjacentDown && !adjacentLeft && !adjacentRight && !adjacentUp)
    {
        score = 1;
    }

    // Return the score
    return score;
}

void Board::placeInFloor(char tileType, int tileCount)
{
    // Iterate over tile line, adding identical char 'tileType' tileCount times
    for (int i = 0; i < tileCount; ++i)
    {
        floorTile->addBack(tileType);
    }
}

// I think this function  is not needed anymore?
void Board::prntMosaic()
{
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            std::cout << mosaic[i][j];
        }
        std::cout << std::endl;
    }
}

void Board::printFloor()
{
    std::cout << "broken: ";

    for (int i = 0; i < floorTile->size(); ++i)
    {
        std::cout << floorTile->get(i) << " ";
    }
}

void Board::prntBoard()
{
    // To print the whole board for the player, we need to print both the pattern lines and mosaic line by line at the same time

    for (int row = 0; row < MOSAIC_DIM; row++)
    {
        std::cout << row + 1 << ": ";

        for (int col = 0; col < MOSAIC_DIM; col++)
        {
            std::cout << patternLines[row][col];
            std::cout << " ";
        }

        std::cout << "|| ";

        for (int col = 0; col < MOSAIC_DIM; col++)
        {
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

void Board::clearFloor()
{
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
    for (int i = 0; i < patternLine; i++)
    {
        if (patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != tileType)
        {
            if (patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != '.')
            {
                validMove = false;
            }
            else
            {
                empty = true;
            }
        }
    }

    if (!empty)
    {
        validMove = false;
    }

    // Check that the mosaic in the chosen row does not contain a tile of the chosen colour, if it does, validMove is false
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        if (mosaic[patternLine - 1][(MOSAIC_DIM - 1) - i] == tileType)
        {
            validMove = false;
        }
    }

    // If either of 1 of these conditions are met, the move cannot be made by the player and they must re-enter their input. Print a meaningful message for the player
    if (!empty)
    {
        std::cout << "The chosen pattern line is full!" << std::endl;
    }
    else if (!validMove)
    {
        std::cout << "The chosen pattern line contains tiles of another colour, or that row already has a tile of that colour on the mosaic." << std::endl;
    }

    return validMove;
}

int Board::resolveBoard()
{
    // Initialise our column int to the back of our pattern line
    int column = MOSAIC_DIM - 1;

    int score = 0;

    // Starting from line one iterate through the pattern lines checking they are full
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        // Initialise a boolean full to default value true, indicating the line is full
        bool full = true;

        // Check if the starting element on the pattern line is empty, if it is we don't need to bother checking the whole line
        if (patternLines[i][column] != '.')
        {
            for (int j = column; j >= (MOSAIC_DIM - 1) - i; j--)
            {
                // For each index of the pattern line, check if there is an empty space character. If so, the pattern line is not full, otherwise full will remain true
                if (patternLines[i][j] == '.')
                {
                    full = false;
                }
            }

            // After the whole line has been checked, if full is still true it means our pattern line is full and a tile should be moved to the mosaic.
            // During this, the score for the tile on the mosaic will also be calculated
            if (full)
            {
                score = score + patternLineToMosaic(i);
            }
        }
    }

    // Remove points based on the tiles in the floor
    int floorTiles;

    // If there are more than 7 floor tiles, the excess are not counted so we set floorTiles to 7, else floorTiles is the amount of tiles there are
    if (floorTile->size() > 7)
    {
        floorTiles = 7;
    }
    else
    {
        floorTiles = floorTile->size();
    }

    // Using our floorScore array, we iterate through and remove points as necessary
    for (int i = 0; i < floorTiles; i++)
    {
        score = score - floorScore[i];
    }

    // After moving all necessary tiles to the pattern line, do a final check of the board to see if any rows are filled (end game condition)
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        int tileCount = 0;
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            // If the current index is not empty, increase tile count
            if (mosaic[i][j] != '.')
            {
                tileCount++;
            }
        }
        // After going through the whole row, if the tile count is 5 that means the row is full, so set rowFilled to true
        if (tileCount == 5)
        {
            rowFilled = true;
        }
    }

    return score;
}

std::string Board::clearBoard()
{
    int column = MOSAIC_DIM - 1;
    std::string tilesCleared;

    // Starting from line one iterate through the pattern lines checking they are full
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        // Initialise a boolean full to default value true, indicating the line is full
        bool full = true;

        // Check if the starting element on the pattern line is empty, if it is we don't need to bother checking the whole line
        if (patternLines[i][column] != '.')
        {
            for (int j = column; j >= (MOSAIC_DIM - 1) - i; j--)
            {
                // For each index of the pattern line, check if there is an empty space character. If so, the pattern line is not full, otherwise full will remain true
                if (patternLines[i][j] == '.')
                {
                    full = false;
                }
            }

            if (full)
            {
                // Add the tiles to our string and then clear the pattern line
                for (int j = column; j >= (MOSAIC_DIM - 1) - i; j--)
                {
                    tilesCleared.push_back(patternLines[i][j]);
                    patternLines[i][j] = '.';
                }
            }
        }
    }

    // Add the tiles to our string from the floor
    for (int i = 0; i < floorTile->size(); i++)
    {
        char tile = floorTile->get(i);
        tilesCleared.push_back(tile);
    }

    // After this is done, clear the floor
    floorTile->clear();

    return tilesCleared;
}

bool Board::isRowFilled()
{
    return rowFilled;
}

int Board::scoreBonus()
{
    // Final scoring rules:
    // 	Additional 2 points per every complete row of 5 tiles
    // 	Additional 7 points for every complete column of 5 tiles
    //  Additional 10 points for every color of tile of which there are 5 on the wall

    int score = 0;

    // Check amount of rows completed:
    int rowsComplete = 0;

    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        int tileCount = 0;
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            // If the current index is not empty, increase tile count
            if (mosaic[i][j] != '.')
            {
                tileCount++;
            }
        }
        // After going through the whole row, if the tile count is 5 that means the row is full, so we increment rowsComplete by 1
        if (tileCount == 5)
        {
            rowsComplete++;
        }
    }

    // Check amount fo columns completed:
    int colComplete = 0;

    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        int tileCount = 0;
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            // If the current index is not empty, increase tile count
            if (mosaic[j][i] != '.')
            {
                tileCount++;
            }
        }
        // After going through the whole column, if the tile count is 5 that means the column is full, so we increment colComplete by 1
        if (tileCount == 5)
        {
            colComplete++;
        }
    }

    // Check how many of each colour tile there is:
    int red = 0;
    int blue = 0;
    int lBlue = 0;
    int yellow = 0;
    int black = 0;

    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            if (mosaic[j][i] == 'R')
            {
                red++;
            }
            else if (mosaic[j][i] == 'U')
            {
                black++;
            }
            else if (mosaic[j][i] == 'Y')
            {
                yellow++;
            }
            else if (mosaic[j][i] == 'B')
            {
                blue++;
            }
            else if (mosaic[j][i] == 'L')
            {
                lBlue++;
            }
        }
    }

    // Add 10 points for every colour that there are 5 of on the mosaic
    if (red == 5)
    {
        score = score + 10;
    }
    else if (black == 5)
    {
        score = score + 10;
    }
    else if (yellow == 5)
    {
        score = score + 10;
    }
    else if (blue == 5)
    {
        score = score + 10;
    }
    else if (lBlue == 5)
    {
        score = score + 10;
    }

    // For every completed row, add 2 points.
    // For every completed column, add 7 points
    score = score + (rowsComplete * 2) + (colComplete * 7);

    // Return the bonus points
    return score;
}

std::string Board::toString()
{
    std::string details = "";
    // Pattern Lines
    for (int row = 0; row < MOSAIC_DIM; row++)
    {
        for (int col = 0; col < (row + 1); col++)
        {
            details += patternLines[row][col];
            details += " ";
        }
        details += "\n";
    }
    // Mosaic
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            details += mosaic[i][j];
            if (!(i == MOSAIC_DIM - 1))
            {
                details += " ";
            }
        }
        details += "\n";
    }
    // Floor line
    for (int i = 0; i < floorTile->size(); i++)
    {
        details += floorTile->get(i);
        if (!(i == floorTile->size() - 1))
        {
            details += " ";
        }
    }

    return details;
}