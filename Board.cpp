#include "Board.h"

Board::Board()
{
    // Initialise our Mosaic to default values. Every index is fill with '.' indicating an empty space
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

    // Initialise the floor
    floorTile = new LinkedList();

    rowFilled = false;
}

Board::Board(std::vector<std::string> patternFileLines, std::vector<std::string> mosaicLines, std::string tileLineString)
{
    // Processes Pattern Lines
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        char tile;

        std::stringstream patternLineStream(patternFileLines.at(i));
        int colNum = 0;

        while (patternLineStream >> tile)
        {
            patternLines[i][4 - colNum] = tile;
            colNum++;
        }
    }

    // Processes Mosaic lines
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        char tile;

        std::stringstream mosaicLineStream(mosaicLines.at(i));
        int colNum = 0;

        while (mosaicLineStream >> tile)
        {
            mosaic[colNum][i] = tile;
            colNum++;
        }

        // Throws an exception is more than five columns are present (i.e. error detected)
        if (!(colNum == 5))
        {
            throw std::exception();
        }
    }

    // Processes Tile Line
    char tile;

    floorTile = new LinkedList();
    std::stringstream tileLineStream(tileLineString);

    while (tileLineStream >> tile)
    {
        floorTile->addBack(tile);
    }
}

Board::~Board()
{
    delete floorTile;
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

    // If we have more tiles than we do empty slots, we place the excess tiles in the floor
    if (tileCount > emptySlot)
    {
        overflow = tileCount - emptySlot;
        placeInFloor(tileType, overflow);
    }

    // Find our starting index place the tiles (skip over tiles already in the pattern line)
    int startIndex = (MOSAIC_DIM - 1) - (patternLine - emptySlot);

    // Place the tiles in pattern line
    for (int i = 0; i < tileCount; i++)
    {
        if (emptySlot > 0)
        {
            patternLines[patternLine - 1][startIndex - i] = tileType;
            --emptySlot;
        }
    }
}

void Board::placeInFloor(char tileType, int tileCount)
{
    // Loop for as many tiles need to be added, adding a tile of that type to the back of the list each time
    for (int i = 0; i < tileCount; ++i)
    {
        floorTile->addBack(tileType);
    }
}

int Board::resolveBoard()
{
    // Initialise our column int to the back of our pattern line. We also start from the end of our column because that is the order that tiles are placed in to the pattern lines
    int column = MOSAIC_DIM - 1;

    int score = 0;

    // Starting from pattern line one iterate through the pattern lines checking they are full
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        // Initialise a boolean 'full' to default value true, used to indicate if the line is full
        bool full = true;

        // Check if the starting element on the pattern line is empty, if it is we don't need to check the rest of the line because we know it's not full
        if (patternLines[i][column] != '.')
        {
            // If the starting element is not empty, then we iterate through the pattern line
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
                // patternLineToMosaic() will return an int indicating the score that the individual move gave the player. This is then added to our score here which is the total gained for the round
                score = score + patternLineToMosaic(i);
            }
        }
    }

    // Remove points based on the tiles in the floor
    int floorTiles = floorTile->size();
    int scoreLost = 0;

    // Using our floorScore array, we iterate through and remove points as necessary. Score lost is added to a seperate int first for the purpose of printing to the user
    for (int i = 0; i < floorTiles; i++)
    {
        scoreLost = scoreLost - floorScore[i];
    }

    std::cout << "Scored " << scoreLost << " point(s) for having " << floorTiles - 1 << " tile(s) in the floor line" << std::endl;

    score = score - scoreLost;

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

    // Return the total score gained/lost for the round to the game
    return score;
}

int Board::patternLineToMosaic(int patternLine)
{
    // If this function is called, we know that a patternline is full and we need to move a tile of a certain colour to our mosaic and then score that move

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

    // We first need to check if the placed tile has any adjacent tiles because this affects the way we score.
    bool adjacentLeft = true;
    bool adjacentRight = true;
    bool adjacentUp = true;
    bool adjacentDown = true;

    // Score for the amount of tiles that are in the row going left. If there are none, or the tile is placed in the first column, we set adjacentLeft to false
    if (position == 0 || mosaic[patternLine][position - 1] == '.')
    {
        adjacentLeft = false;
    }
    else
    {
        int curPos = position;
        // Iterate through our mosaic moving left. The loop will continue until an empty space or the edge of the mosaic is reached and a point will be added for each tile
        while (mosaic[patternLine][curPos] != '.' && curPos >= 0)
        {
            score++;
            curPos--;
        }
    }

    // Score for the amount of tiles that are in the row going right. If there are none, or the tile is placed in the last column, we set adjacentRight to false
    if (position == 4 || mosaic[patternLine][position + 1] == '.')
    {
        adjacentRight = false;
    }
    else
    {
        int curPos = position;
        // If there are adjacent tiles to the left it means we have already counted the placed tile in the scoring, which means we need to remove a point so the tile is not counted twice for the same row
        if (adjacentLeft)
        {
            score--;
        }
        // Iterate through our mosaic moving right. The loop will continue until an empty space or the edge of the mosaic is reached and a point will be added for each tile
        while (mosaic[patternLine][curPos] != '.' && curPos < MOSAIC_DIM)
        {
            score++;
            curPos++;
        }
    }

    // Score for the amount of tiles that are in the column going up. If there are none, or the tile is placed in the first row, we set adjacentUp to false
    if (patternLine == 0 || mosaic[patternLine - 1][position] == '.')
    {
        adjacentUp = false;
    }
    else
    {
        int curRow = patternLine;
        // Iterate through our mosaic moving up. The loop will continue until an empty space or the edge of the mosaic is reached and a point will be added for each tile
        while (mosaic[curRow][position] != '.' && curRow >= 0)
        {
            score++;
            curRow--;
        }
    }

    // Score for the amount of tiles that are in the column going down. If there are none, or the tile is placed in the last row, we set adjacentUp to false
    if (patternLine == 4 || mosaic[patternLine + 1][position] == '.')
    {
        adjacentDown = false;
    }
    else
    {
        int curRow = patternLine;
        // If there are adjacent tiles above it means we have already counted the placed tile in the scoring, which means we need to remove a point so the tile is not counted twice for the same column
        if (adjacentUp)
        {
            score--;
        }
        // Iterate through our mosaic moving down. The loop will continue until an empty space or the edge of the mosaic is reached and a point will be added for each tile
        while (mosaic[curRow][position] != '.' && curRow < MOSAIC_DIM)
        {
            score++;
            curRow++;
        }
    }

    // If our placed tile has no adjacent tiles, then the score is just 1
    if (!adjacentDown && !adjacentLeft && !adjacentRight && !adjacentUp)
    {
        score = 1;
    }

    std::cout << "Scored " << score << " point(s) for moving tile " << tile << " to mosaic in Row " << patternLine + 1 << std::endl;

    // Return the score
    return score;
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

        // After each row of the pattern lines has been printed, print a divider
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
    std::cout << "broken: ";

    for (int i = 0; i < floorTile->size(); ++i)
    {
        std::cout << floorTile->get(i) << " ";
    }

    std::cout << std::endl;
}

void Board::clearFloor()
{
    floorTile->clear();
}

bool Board::isRowFilled()
{
    return rowFilled;
}

std::string Board::clearBoard()
{
    int column = MOSAIC_DIM - 1;

    // String to store the tiles that have been cleared
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

            // If the pattern line is full, it means a tile has been moved to the mosaic and the pattern line needs to be cleared
            if (full)
            {
                // Add the tiles one by one to our string and then clear the pattern line by setting the char to the empty space char
                for (int j = column; j >= (MOSAIC_DIM - 1) - i; j--)
                {
                    tilesCleared.push_back(patternLines[i][j]);
                    patternLines[i][j] = '.';
                }
            }
        }
    }

    // Add all times from the floor to the string as these are always removed after each round
    for (int i = 0; i < floorTile->size(); i++)
    {
        char tile = floorTile->get(i);
        tilesCleared.push_back(tile);
    }

    // After this is done, clear the floor
    floorTile->clear();

    return tilesCleared;
}

bool Board::checkBoard(int patternLine, char tileType)
{
    bool validMove = true;
    bool freeSpace = false;

    // Check that the chosen pattern line contains ONLY either empty spaces OR tiles of the chosen colour, if not, validMove is false. Also ensures there is at least one empty space in the pattern line
    for (int i = 0; i < patternLine; i++)
    {
        // If the current index of our pattern line does not contain our given tile type, we need to check if it's instead empty
        if (patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != tileType)
        {
            // If the curen index of the pattern line does not contain an empty space char, then it means that it contains another tile colour and therefore the move is not valid
            if (patternLines[patternLine - 1][(MOSAIC_DIM - 1) - i] != '.')
            {
                validMove = false;
            }
            else
            {
                freeSpace = true;
            }
        }
    }

    if (!freeSpace)
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
    if (!freeSpace)
    {
        std::cout << "The chosen pattern line is full!" << std::endl;
    }
    else if (!validMove)
    {
        std::cout << "The chosen pattern line contains tiles of another colour, or that row already has a tile of that colour on the mosaic." << std::endl;
    }

    return validMove;
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

    // Check amount of columns completed:
    int colComplete = 0;

    // To be clear, this is the exact same loop as above, except j and i are switched so that we instead check column by column
    for (int j = 0; j < MOSAIC_DIM; j++)
    {
        int tileCount = 0;
        for (int i = 0; i < MOSAIC_DIM; i++)
        {
            // If the current index is not empty, increase tile count
            if (mosaic[i][j] != '.')
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

    // We iterate through our entire mosaic checking index by index and counting the colours
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

    // For each colour that there is 5 of on the mosaic, add an additional 10 points
    if (red == 5)
    {
        score = score + 10;
        std::cout << "Bonus 10 points for having 5 red tiles!" << std::endl;
    } 
    if (black == 5)
    {
        score = score + 10;
        std::cout << "Bonus 10 points for having 5 black tiles!" << std::endl;
    }
    if (yellow == 5)
    {
        score = score + 10;
        std::cout << "Bonus 10 points for having 5 yellow tiles!" << std::endl;
    }
    if (blue == 5)
    {
        score = score + 10;
        std::cout << "Bonus 10 points for having 5 blue tiles!" << std::endl;
    }
    if (lBlue == 5)
    {
        score = score + 10;
        std::cout << "Bonus 10 points for having 5 light blue tiles!" << std::endl;
    }

    // For every completed row, add 2 points.
    // For every completed column, add 7 points
    score = score + (rowsComplete * 2) + (colComplete * 7);

    std::cout << (rowsComplete * 2) << " bonus points for having " << rowsComplete << " completed row(s)" << std::endl;
    std::cout << (rowsComplete * 7) << " bonus points for having " << colComplete << " completed column(s)" << std::endl;

    // Return the bonus points
    return score;
}

int Board::countRows()
{
    // Same method used in scoring the bonus but this functon is only called on in the event of a tie-breaker
    int rowsFilled = 0;

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
        // After going through the whole row, if the tile count is 5 that means the row is full, so we increment the amount of rowsFilled by 1
        if (tileCount == 5)
        {
            rowsFilled++;
        }
    }

    return rowsFilled;
}

int Board::floorSlot()
{
    return FLOOR_SIZE - floorTile->size();
}

char Board::removeLastFloorTile()
{
    char tile = floorTile->get(floorTile->size() - 1);
    floorTile->removeBack();
    return tile;
}

std::string Board::toString()
{
    std::string details = "\n";

    // Pattern Lines
    for (int row = 0; row < MOSAIC_DIM; row++)
    {
        for (int col = 0; col < MOSAIC_DIM; col++)
        {
            if (col + 1 >= MOSAIC_DIM - row)
            {
                details += patternLines[row][col];
                details += " ";
            }
        }
        details += "\n";
    }

    // Mosaic
    for (int i = 0; i < MOSAIC_DIM; i++)
    {
        for (int j = 0; j < MOSAIC_DIM; j++)
        {
            details += mosaic[i][j];
            details += " ";
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
    details += "\n";

    return details;
}