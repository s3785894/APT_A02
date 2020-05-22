#include "Game.h"
#include <sstream>
#include <exception>

Game::Game(std::string playerOneName, std::string playerTwoName, std::string seed, bool hasSeeded)
{
    // Create our player objects using the provided names from the user input
    player1 = std::shared_ptr<Player>(new Player(playerOneName));
    player2 = std::shared_ptr<Player>(new Player(playerTwoName));

    // Create our table object. If a seed is provided, we need to pass the seed through to the bag
    if (!hasSeeded)
    {
        table = std::shared_ptr<Table>(new Table());
    }
    else
    {
        table = std::shared_ptr<Table>(new Table(seed));
    }

    current = nullptr;
    gameEnd = false;
}

Game::Game(std::ifstream &fileInput)
{
    loadGame(fileInput);
}

Game::~Game()
{
}

void Game::playGame(bool isMidRound)
{
    // If we start the game mid round (the game is started from a loaded save file), we need to skip the round intialisation so the round progress is not reset
    bool *skipInitilisation = new bool(isMidRound);

    // Loop round by round, each time a round is played, we check if the game end condition has been met before starting a new round
    while (!checkEnd())
    {
        if (!(*skipInitilisation))
        {
            table->initialiseRound();
        }

        playRound();

        *skipInitilisation = false;
    }

    // If we're exiting the game loop, it means that the end game condition has been met. Therefore, we need to do the final scoring and determine a winner
    scoreGame();
}

void Game::initialiseRound()
{
    table->initialiseRound();
}

void Game::playRound()
{
    std::cout << "====== Start Round ======" << std::endl;
    std::cout << std::endl;

    // Checks if there is no "current player" (i.e. this is the first round of a new game)
    // This condition is not met for a turn of a loaded round - therefore, it allows for rounds to continue from their last position
    // By default, player 1 is assigned to be the first player for the game
    if (current == nullptr)
    {
        current = player1.get();
    }

    // Loops turns within rounds until round end condition (no tiles left) is met
    while (table->tilesLeft())
    {
        // Handle the player's turn
        playerTurn();

        // After each turn, switch the current player
        if (current == player1.get())
        {
            current = player2.get();
        }
        else
        {
            current = player1.get();
        }
    }

    // If we're exiting the loop, it means the end round condition has been met and we need to score the round and then clear the player's boards for the next round
    scoreRound();
    clearBoards();

    std::cout << "====== End Round ======" << std::endl;
    std::cout << std::endl;
}

void Game::playerTurn()
{
    // User input variables
    int factory;
    int patternLine;
    char tile;
    bool validInput = false;
    bool lastCommandSave = false;
    bool lastCommandMosaic = false;

    std::cout << "TURN FOR PLAYER: " << current->getName() << std::endl
              << std::endl;

    // Print player board and table so the player can see what they're doing
    table->printFactoryContents();
    current->prntBoard();

    while (!validInput)
    {
        std::cout << "Enter turn input: " << std::endl;
        std::cout << "> ";

        // Takes input and process it into vector for analysis (allows command line arguments)
        std::string turnInput;
        while (std::getline(std::cin, turnInput) && turnInput.empty())
        {
            // N/A - a loop is needed for getline to function here without a segfault occuring
        }

        std::stringstream turnInputStream(turnInput);
        std::string arg;
        std::vector<std::string> turnArgs;

        while (turnInputStream >> arg)
        {
            turnArgs.push_back(arg);
        }

        lastCommandSave = false;
        lastCommandMosaic = false;

        // Convert the first string (which determines what action is taken) to lowercase so that it's case insensitive
        std::string turnInputLower = turnArgs.front();
        std::transform(turnInputLower.begin(), turnInputLower.end(), turnInputLower.begin(), ::tolower);

        // Save the game, then continue the turn
        if (turnInputLower == "save" && turnArgs.size() == 2)
        {
            saveGame(turnArgs.at(1));
            lastCommandSave = true;
        } else  if (turnInputLower == "save" && turnArgs.size() > 2)
        {
            std::cout << "Filename must not contain spaces. Please try again." << std::endl;
        }

        // Exit the game without auto saving
        if (turnInputLower == "exit")
        {
            std::cout << "Exiting Program!" << std::endl;
            exit(EXIT_SUCCESS);
        }

        // Execute regular turn
        if (turnInputLower == "turn")
        {
            if (turnArgs.size() == 4)
            {
                try
                {
                    factory = std::stoi(turnArgs.at(1));
                    tile = toupper(turnArgs.at(2)[0]);

                    // Convert the pattern line input to lowercase so we can do a comparison
                    std::string patternLineInput = turnArgs.at(3);
                    std::transform(patternLineInput.begin(), patternLineInput.end(), patternLineInput.begin(), ::tolower);

                    // Check if the input (to lowercase) was 'floor', if so, convert it to pattern line 6.
                    if(patternLineInput == "floor")
                    {
                        patternLine = 6;
                    } 
                    // Else, process as usual
                    else 
                    {
                        patternLine = std::stoi(turnArgs.at(3));
                    }
                    
                    validInput = validateInput(factory, tile, patternLine);

                    if (validInput)
                    {
                        validInput = table->checkFactory(factory, tile);
                    }

                    if (validInput && patternLine != 6)
                    {
                        validInput = current->checkBoard(patternLine, tile);
                    }
                }
                catch (std::exception e)
                {
                    std::cout << "Error occured when making turn. Please try again, in the correct format." << std::endl;
                }
            }
        }

        // Print out the format of the mosaic to the player so they know which tiles go where
        if (turnInputLower == "mosaic")
        {
            std::string mosaicColours =
                "\n \
                B Y R U L   \n \
                L B Y R U   \n \
                U L B Y R   \n \
                R U L B Y   \n \
                Y R U L B   \n \
                ";

            std::cout << mosaicColours << std::endl;

            lastCommandMosaic = true;
        }

        // Check if input is still invalid to print out a message to the user before re-entering the loop so they can try again
        if (!validInput && !lastCommandSave && !lastCommandMosaic)
        {
            std::cout << "Invalid input." << std::endl;
        }
    }

    // If we've reach here we know we've been given a valid user input, so we can now execute the logic for taking the turn
    // Move tiles to their respective spots.
    if (patternLine != 6)
    {
        current->placeTiles(patternLine, tile, table->takeTiles(factory, tile));
    }

    // If the pattern line is 6 (floor), we call on the place in floor function instead
    if (patternLine == 6)
    {
        std::string tileOverflow;
        int tileFrequency = table->takeTiles(factory, tile);
        //if floor is full, place tiles in box lid
        if (current->hasFloorSlot() == 0)
        {
            for (int i = 0; i < tileFrequency; i++)
            {
                tileOverflow.push_back(tile);
            }
            table->placeInLid(tileOverflow);
            //if floor does not have enough slots, fill the floor and put excess to box lid
        }
        else if (current->hasFloorSlot() < tileFrequency)
        {
            int addToLid = tileFrequency - current->hasFloorSlot();
            current->placeInFloor(tile, current->hasFloorSlot());
            for (int i = 0; i < addToLid; i++)
            {
                tileOverflow.push_back(tile);
            }
            table->placeInLid(tileOverflow);
            //else, add tiles to floor
        }
        else
        {
            current->placeInFloor(tile, tileFrequency);
        }
    }

    // If taking from the centre table, and the first player token has not been taken, give it to the player
    if (factory == 0 && table->checkFirstPlayerToken())
    {
        //if floor is full, move the last tile of the floor to box lid and add the first player token to floor
        if (current->hasFloorSlot() == 0)
        {
            std::string tileOverflow;
            tileOverflow.push_back(current->removeFromFloor());
            table->placeInLid(tileOverflow);
        }
        current->placeInFloor('F', 1);
        //first = current;
    }

    std::cout << std::endl;
    current->prntBoard();
}

bool Game::checkEnd()
{
    bool gameEnd = false;

    // If either player has a full row on their board, the end game condition has been met
    if (player1->isRowFilled() == true || player2->isRowFilled() == true)
    {
        gameEnd = true;
    }

    return gameEnd;
}

void Game::saveGame(std::string fileName)
{
    // Gather the game information from their 'toString' functions, formatted to the structure of the save file format

    std::ofstream saveFile;
    saveFile.open(fileName);

    if (saveFile.is_open())
    {
        bool isPlayer1Current = false;
        if (current == player1.get())
        {
            isPlayer1Current = true;
        }
        saveFile << table->toString();
        saveFile << player1->toString(isPlayer1Current);
        saveFile << player2->toString(!isPlayer1Current);
    }

    saveFile.close();

    std::cout << "GAME SAVED" << std::endl;
}

void Game::scoreRound()
{
    std::cout << "Round Scoring" << std::endl;
    LINE_DIVIDER

    // Resolve the board and score the round for each player
    player1->resolveBoard();
    std::cout << std::endl;
    player2->resolveBoard();

    // Print out the players total score after adding the round score
    std::cout << std::endl;
    std::cout << player1->getName() << "'s total score: " << player1->getScore() << std::endl;
    std::cout << player2->getName() << "'s total score: " << player2->getScore() << std::endl;
    std::cout << std::endl;
}

void Game::clearBoards()
{
    // Clear the player boards of the necessary tiles, retrieving the cleared tiles as a string
    std::string player1String = player1->clearBoard();
    std::string player2String = player2->clearBoard();

    // Take the cleared tiles from both player's board and combine them into a single string
    std::string tiles = player1String + player2String;

    // Give this string to the table so it can be passed to bag and the discarded tiles can be placed in the box lid
    table->placeInLid(tiles);
}

bool Game::validateInput(int factory, char tile, int patternLine)
{

    // Need to do range checking.
    // turnInput[0] should be 0-5 inclusive (factory)
    // turnInput[1] should match a possible tile color (tile)
    // turnInput[2] should be 1-6 inclusive (patternLine) - patterLine 6 represents the floor

    bool validInput = false;

    if (0 <= factory && factory <= 5)
    {
        // Factory input is within range, check pattern line range
        if (1 <= patternLine && patternLine <= 6)
        {
            // Pattern line input is within range, check if the given tile colour is valid
            // Check the tile colour input against our array of tile colours
            for (int i = 0; i < NUM_COLOURS; i++)
            {
                if (tile == tileColours[i])
                {
                    // If tile matches a possible tile colour then we know the previously checked inputs were also valid, meaning the entire input is valid.
                    validInput = true;
                }
            }
        }
    }

    return validInput;
}

void Game::scoreGame()
{
    // Final scoring rules:
    // 	Additional 2 points per every complete row of 5 tiles
    // 	Additional 7 points for every complete column of 5 tiles
    //  Additional 10 points for every color of tile of which there are 5 on the wall

    // After these extra points have been added, the player with the highest score wins.
    // If the game is a tie, whoever has the most completed rows wins - Need to therefore check for this

    // Calculate the end game bonuses for each player
    std::cout << "Score Bonuses for: " << player1->getName() << std::endl;
    player1->scoreBonus();

    std::cout << "Score Bonuses for: " << player2->getName() << std::endl;
    player2->scoreBonus();

    // Get the final scores for each player
    int player1Score = player1->getScore();
    int player2Score = player2->getScore();

    std::cout << player1->getName() << "'s final score: " << player1Score << std::endl;
    std::cout << player2->getName() << "'s final score: " << player2Score << std::endl;
    std::cout << std::endl;

    std::string winner;

    if (player1Score > player2Score)
    {
        winner = player1->getName();
    }
    else if (player2Score > player1Score)
    {
        winner = player2->getName();
    }
    else
    {
        // Check who has the most rows completed
        // If the number of rows is even, the game ends in a tie
        if (player1->countRows() > player2->countRows())
        {
            winner = player1->getName();
        }
        else if (player2->countRows() > player1->countRows())
        {
            winner = player2->getName();
        }
        else
        {
            winner = "No-One! The game ends in a tie";
        }
    }

    std::cout << "The winner is: " << winner << "!" << std::endl;
    std::cout << std::endl;
}

void Game::loadGame(std::ifstream &fileInput)
{
    try
    {
        // Takes all lines of the input file and place them into a vector
        std::vector<std::string> fileLines;
        std::string line;

        while (std::getline(fileInput, line))
        {
            fileLines.push_back(line);
        }

        // Throws an exception if the amount of lines (defined save data) is not exact (i.e. modified file)
        if (!(fileLines.size() == 36))
        {
            throw std::exception();
        }

        // Checks the current player via Player 1's current player state
        bool isPlayerOneCurrent = false;
        if (fileLines.at(9) == "True" || fileLines.at(9) == "False")
        {
            if (fileLines.at(9) == "True")
            {
                isPlayerOneCurrent = true;
            }
        }
        // Throws an exception if the player is not listed as either True or False
        else
        {
            throw std::exception();
        }

        // Takes file lines from vector that relate to the table and pass them into the table via a constructor
        std::vector<std::string> loadedTable;
        for (int i = 0; i < 8; i++)
        {
            loadedTable.push_back(fileLines.at(i));
        }
        table = std::shared_ptr<Table>(new Table(loadedTable));

        // Take file lines from vector that relate to each player (+ their board) and pass them into their individual player objects
        std::vector<std::string> loadPlayer1;
        for (int i = 8; i < 22; i++)
        {
            loadPlayer1.push_back(fileLines.at(i));
        }
        player1 = std::shared_ptr<Player>(new Player(loadPlayer1));

        std::vector<std::string> loadPlayer2;
        for (int i = 22; i < fileLines.size(); i++)
        {
            loadPlayer2.push_back(fileLines.at(i));
        }
        player2 = std::shared_ptr<Player>(new Player(loadPlayer2));

        // Sets up current player
        if (isPlayerOneCurrent)
        {
            current = player1.get();
        }
        else
        {
            current = player2.get();
        }
    }
    catch (...)
    {
        std::cout << "An error has occured when loading the file. Incorrect file format detected. Terminating program." << std::endl;
        exit(EXIT_SUCCESS);
    }
}