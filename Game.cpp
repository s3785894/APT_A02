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
    if (this->current == nullptr)
    {
        this->current = player1.get();
    }

    // Loops turns within rounds (and turns) until round end condition is met
    // while (table->tilesLeft())
    // {
        std::cout << "TURN FOR PLAYER: " << this->current->getName() << std::endl;
        std::cout << std::endl;

        table->printFactoryContents();

        current->prntBoard();



       /* std::string turnInput;
        bool validInput = false;
        while (!validInput)
        {
            std::cout << "> ";
            if (std::cin.good())
            {
                std::cin >> turnInput;
                if (turnInput == "save")
                {
                    this->saveGame();
                }
                else
                {
                    // check to see if the command is four words, the first being turn
                    // and then check to see if factory, colour, and storage row are input correctly
                    // and then check to see if the move is possible with current mosaic, storage row, and factory
                }
            }
            else
            {
                std::cout << "Invalid input." << std::endl;
            }
        }*/

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
}