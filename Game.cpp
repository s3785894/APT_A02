#include "Game.h"
#include <sstream>

Game::Game(std::string playerOneName, std::string playerTwoName)
{
    this->player1 = new Player(playerOneName);
    this->player2 = new Player(playerTwoName);
    this->table = new Table();
    this->current = nullptr;
    this->gameEnd = false;
}

Game::Game(std::ifstream &fileInput)
{
    // take input based on whatever file format we need to use
}

Game::~Game()
{
    delete this->player1;
    delete this->player2;
    delete this->table;
    delete this->current;
}

void Game::playGame()
{
    // Loop while end game condition is not met
    // For each loop, playRound(), then checkEnd()

    while (!gameEnd)
    {
        playRound();
        checkEnd();
    }

    // Game over
    // Finish last scoring and then determine winner
}

void Game::playRound()
{
    std::cout << "====== Start Round ======" << std::endl;

    // Checks if there is no "current player" (i.e. this is a new game or round) and automatically assigns the player's turn
    // This condition is not met for a turn of a loaded round - therefore, it allows for rounds to continue from their last position
    if (this->current == nullptr)
    {
        this->current = this->player1;
    }

    // Loops turns within rounds (and turns) until round end condition is met
    while (table->tilesLeft())
    {
        std::cout << "Turn for player: " << this->current->getName() << std::endl;
        std::string turnInput;
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
        }
        // Switch current player to the opposite player in the game
        if (this->current == this->player1)
        {
            this->current = this->player2;
        }
        else if (this->current == this->player2)
        {
            this->current = this->player1;
        }
    }

    std::cout << "====== End Round ======" << std::endl;
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