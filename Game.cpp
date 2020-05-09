#include "Game.h"
#include <sstream>

Game::Game(std::string playerOneName, std::string playerTwoName)
{
    player1 = std::shared_ptr<Player>(new Player(playerOneName));
    player2 = std::shared_ptr<Player>(new Player(playerTwoName));

    table = std::shared_ptr<Table>(new Table());

    this->current = nullptr;
    this->gameEnd = false;
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

    while (!gameEnd)
    {
        initialiseRound();
        playRound();
        checkEnd();

        gameEnd = true;
    }

    // Game over
    // Finish last scoring and then determine winner
}

void Game::initialiseRound(){
    table->initialiseRound();
}

void Game::playRound()
{
    std::cout << "====== Start Round ======" << std::endl;
    std::cout << std::endl;
    
    // Checks if there is no "current player" (i.e. this is a new game or round) and automatically assigns the player's turn
    // This condition is not met for a turn of a loaded round - therefore, it allows for rounds to continue from their last position
    // By default, player 1 is assigned to be the first player for the game
    if (current == nullptr)
    {
        current = player1.get();
    }

    // User input variables
    int factory;
    int patternLine;
    char tile;

    // Loops turns within rounds (and turns) until round end condition is met
    // while (table->tilesLeft())
    // {
        std::cout << "TURN FOR PLAYER: " << current->getName() << std::endl;
        std::cout << std::endl;

        table->printFactoryContents();
        current->prntBoard();


        std::string turnInput;
        bool validInput = false;
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
                    // exit gane (without saving)
                }

                if(turnInput.length() == 3){
                    // These conversions need to happen here as the value of these variables needs to be used to take the turn.
                    // Convert factory/pattern line to int. Need to -48 because of how the numbers are represented by ASCII numbers (0 is 48, 1 is 49, etc.)
                    factory = turnInput[0] - 48;
                    patternLine = turnInput[2] - 48;
                    // Assign tile colour choice to individual char
                    tile = turnInput[1];
                            
                    // Pass the variables into our validation function so that range checking can be completed.
                    validInput = validateTurn(factory, tile, patternLine);
                }
         
            }
            else
            {
                std::cout << "Invalid input." << std::endl;
            }

            // Check if input is still invalid to print out a message to the user before re-entering the loop
            if(!validInput){
                std::cout << "Invalid input." << std::endl;
            }
        }


        // We've been given a valid user input, so we can now execute the logic for taking the turn
        // Move tiles to their respective spots. 

       // playerTurn(factory, tile, patternLine);


        // The player who takes the first run in the round is decided by who has the first player token, it's not alternating

        // Need to check for frst player token
    //}

    std::cout << "====== End Round ======" << std::endl;
    std::cout << std::endl;
}

void Game::checkEnd()
{
    // Check the players board for a full horizontal row (maybe call on a function in player that does this)

    // if(horizontal row complete){
    //     this->gameEnd = true;
    // }
}

void Game::saveGame()
{
    // Needs to get Players, their Boards, Bag, Lid(?), and Table via getters and setters
    // Alternatively, make use of custom toString methods to convert everything to string

    std::cout << "GAME SAVED" << std::endl;
}

bool Game::validateTurn(int factory, char tile, int patternLine) 
{

    // Need to do range checking.
    // turnInput[0] should be 0-5 inclusive (factory)
    // turnInput[1] should match a possible tile color (tile)
    // turnInput[2] should be 1-5 inclusive (patternLine)

    bool validInput = false;

    if(0 <= factory && factory <= 5) {
        // Valid, check next
        if(1 <= patternLine && patternLine <= 5) {
            // Valid, check next
            // Check the tile colour input against our array of tile colours
            for(int i = 0; i < NUM_COLOURS; i++){
                if(toupper(tile) == tileColours[i]){
                    // If tile matches a possible tile colour then we know the previously checked inputs were also valid, meaning the entire input is valid.
                        validInput = true;
                    }
            }
                
        }
    }

    return validInput;
}

void playerTurn(int factory, char tile, int patternLine)
{

}