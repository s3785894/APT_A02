#include "Game.h"

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
    if (this->current == nullptr)
    {
        this->current = player1;
    }

    // Loops turns within rounds (and turns) until round end condition is met
    while (table->tilesLeft())
    {
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
        // switch current player to other player
    }

    // Execute scoring part of round

    std::cout << "====== End Round ======" << std::endl;
}

void Game::checkEnd()
{
    // Check the players board for a full horizontal row (maybe call on a function in player that does this)

    // if(horizontal row complete){
    //     gameEnd = true;
    // }
}

void Game::saveGame()
{
    // Needs to get Players, their Boards, Bag, Lid(?), and Table via getters and setters
    // Alternatively, make use of custom toString methods to convert everything to string
}