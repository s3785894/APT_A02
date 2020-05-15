#include "Game.h"
#include <sstream>

Game::Game(std::string playerOneName, std::string playerTwoName, std::string seed, bool hasSeeded)
{
    player1 = std::shared_ptr<Player>(new Player(playerOneName));
    player2 = std::shared_ptr<Player>(new Player(playerTwoName));

    if (!hasSeeded)
    {
        table = std::shared_ptr<Table>(new Table());
    }
    else
    {
        table = std::shared_ptr<Table>(new Table(seed));
    }

    current = nullptr;
    //first = nullptr;
    gameEnd = false;
}

Game::Game(std::ifstream &fileInput)
{
    // take input based on whatever file format we need to use
}

Game::~Game()
{
    //delete this->current; -- Throws an error because ptr value is null
}

void Game::playGame()
{
    // Loop while end game condition is not met
    // For each loop, playRound(), then checkEnd()

    while (!checkEnd())
    {
        table->initialiseRound();
        playRound();
    }

    // If we're exiting the above loop, it means that the end game condition has been met. Therefore, we need to do the final scoring and determine a winner
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

    // Checks if there is no "current player" (i.e. this is the first round of a new game) and automatically assigns the player's turn
    // This condition is not met for a turn of a loaded round - therefore, it allows for rounds to continue from their last position
    // By default, player 1 is assigned to be the first player for the game
    if (current == nullptr)
    {
        current = player1.get();
    }

    // Loops turns within rounds until round end condition (no tiles left) is met
    while (table->tilesLeft())
    {
        // Take the player's turn
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

    std::string turnInput;
    bool validInput = false;

    std::cout << "TURN FOR PLAYER: " << current->getName() << std::endl
              << std::endl;

    // Print player board and table so the player can see what they're doing
    table->printFactoryContents();
    current->prntBoard();

    std::cout << "Enter turn input: " << std::endl;

    while (!validInput)
    {
        std::cout << "> ";
        if (std::cin.good())
        {
            std::cin >> turnInput;

            // Save the game, then continue the turn
            if (turnInput == "save")
            {
                saveGame();
            }

            if (turnInput == "exit")
            {
                exit(EXIT_SUCCESS);
            }

            if (turnInput.length() == 3)
            {
                // These conversions need to happen here as the value of these variables needs to be used to take the turn.
                // Convert factory/pattern line to int. Need to -48 because of how the numbers are represented by ASCII numbers (0 is 48, 1 is 49, etc.)
                factory = turnInput[0] - 48;
                patternLine = turnInput[2] - 48;
                // Assign tile colour choice to individual char and convert to upper case since tiles are always represented as uppercase chars
                tile = toupper(turnInput[1]);

                // Pass the variables into our validation function so that range checking can be completed.
                validInput = validateInput(factory, tile, patternLine);

                // If the input is valid, we then need to check if it's a valid move (If the chosen factory contains the chosen tile colour)
                if (validInput)
                {
                    validInput = table->checkFactory(factory, tile);
                }

                // If the previous validation check passes, check if it's a valid move for the player board
                if (validInput && patternLine != 6)
                {
                    validInput = current->checkBoard(patternLine, tile);
                }
            }
        }

        if (turnInput == "exit")
        {
            // exit gane (without saving)
        }

        // Check if input is still invalid to print out a message to the user before re-entering the loop so they can try again
        if (!validInput)
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
        current->placeInFloor(tile, table->takeTiles(factory, tile));
    }

    // If taking from the centre table, and the first player token has not been taken, give it to the player
    if (factory == 0 && table->checkFirstPlayerToken())
    {
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
    if(player1->isRowFilled() == true || player2->isRowFilled() == true){
        gameEnd = true;
    }

    return gameEnd;
}

void Game::saveGame()
{
    // Needs to get Players, their Boards, Bag, Lid(?), and Table via getters and setters
    // Alternatively, make use of custom toString methods to convert everything to string

    std::cout << "GAME SAVED" << std::endl;
}

void Game::scoreRound()
{
    std::cout << "Round Scoring" << std::endl; 
    player1->resolveBoard();

    player2->resolveBoard();

    std::cout << player1->getName() << "'s total score: " << player1->getScore() << std::endl;
    std::cout << player2->getName() << "'s total score: " << player2->getScore() << std::endl;
}

void Game::clearBoards()
{
    std::string player1String = player1->clearBoard();
    std::string player2String = player2->clearBoard();

    std::string tiles = player1String + player2String;

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
        // Valid, check next
        if (1 <= patternLine && patternLine <= 6)
        {
            // Valid, check next
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

void Game::scoreGame(){
    // Final scoring rules:
	// 	Additional 2 points per every complete row of 5 tiles 
	// 	Additional 7 points for every complete column of 5 tiles
    //  Additional 10 points for every color of tile of which there are 5 on the wall

    // After these extra points have been added, the player with the highest score wins. 
    // If the game is a tie, whoever has the most completed rows wins - Need to therefore check for this

    // Calculate the end game bonuses for each player
    player1->scoreBonus();
    player1->scoreBonus();

    // Get the final scores for each player
    int player1Score = player1->getScore();
    int player2Score = player2->getScore();

    std::cout << player1->getName() << "'s final score: " << player1Score << std::endl;
    std::cout << player2->getName() << "'s final score: " << player2Score << std::endl;

    if(player1Score > player2Score){
        std::cout << player1->getName() << " is the Winner!" << std::endl;
    } else if(player2Score > player1Score){
        std::cout << player2->getName() << " is the Winner!" << std::endl;
    } else {
        // Scores are tied -- TO DO
    }
}







