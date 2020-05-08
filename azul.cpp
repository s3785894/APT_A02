#include <iostream>
#include <fstream>
#include <exception>

#include "Types.h"
#include "Bag.h"
#include "Game.h"

int displayMenu();
void printCredits();
void newGame();
void loadGame();
void howTo();

int main(void)
{

    bool exit = false;

    while (!exit)
    {
        int mode = displayMenu();

        if (mode == 1)
        {
            newGame();
        }
        else if (mode == 2)
        {
            loadGame();
        }
        else if (mode == 3)
        {
            printCredits();
        }
        else if (mode == 4)
        {
            howTo();
        }
        else if (mode == 5)
        {
            std::cout << "Exiting Program!" << std::endl;
            exit = true;
        }
    }

    return EXIT_SUCCESS;
}

int displayMenu()
{
    std::cout << "Welcome to Azul!" << std::endl;
    LINE_DIVIDER
    std::cout << "\nMenu" << std::endl;
    LINE_DIVIDER
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. How To" << std::endl;
    std::cout << "5. Quit" << std::endl;

    int input = -1;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "> ";
        if (std::cin.good())
        {
            std::cin >> input;
            if (input > 0 && input <= 5)
            {
                validInput = true;
            }
            else
            {
                std::cout << "Invalid menu selection. Please enter the number preceeding any of the menu options above." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid input." << std::endl;
        }
    }

    return input;
}

void printCredits()
{

    std::cout << "CREDITS: " << std::endl;
    LINE_DIVIDER
    std::cout << "Student 1:" << std::endl;
    std::cout << STUDENT_ONE << std::endl
              << std::endl;

    std::cout << "Student 2:" << std::endl;
    std::cout << STUDENT_TWO << std::endl
              << std::endl;

    std::cout << "Student 3:" << std::endl;
    std::cout << STUDENT_THREE << std::endl;
    LINE_DIVIDER

    std::cout << std::endl;
}

void newGame()
{
    std::string playerOneName;
    std::string playerTwoName;

    std::cout << "Enter name for Player 1: " << std::endl;
    std::cin >> playerOneName;

    std::cout << "Enter name for Player 2: " << std::endl;
    std::cin >> playerTwoName;

    std::unique_ptr<Game> game(new Game(playerOneName, playerTwoName));
    game->playGame();
}

void loadGame()
{
    // TODO: improve filename input validation, fix errors with throwing file stream exception, fix game constructor
    std::cout << "Enter the filename from which to load the game" << std::endl;
    try
    {
        std::string filename;
        std::cin >> filename;
        std::ifstream fileInput(filename);
        if (!fileInput.good())
        {
            //throw std::ios_base::failure;
        }

        std::unique_ptr<Game> game(new Game(fileInput));
        game->playGame();
    }
    catch (std::ios_base::failure e)
    {
        std::cout << "Error when accessing file - please ensure file exists before attempting to load it.";
    }
}

void howTo()
{
    std::string string =
        "\n \
        HOW TO: \n \
        \n \
        Follow the basic input instructions on screen to begin the game. If at any point you enter an input that is not valid, \n \
        you will simply be asked to try again until you enter a valid input. \n \
        \n \
        When playing the game, the input for a turn is in the format of [FACTORY][TILE][PATTERN LINE]. No spaces should be used. \n \
        \n \
        For example, if you want to take all the blue tiles from factory 2, and place them in your 3rd pattern line,\n \
        the input would be: \n \
        2B3 \n \
        \n \
        If at any point you would like to save your game, type 'save'. This will save the game in it's current state and then\n \
        continue the current turn\n \
        \n \
        To exit the game, type 'exit'. This will exit WITHOUT saving.\n \
        ";

    std::cout << string << std::endl;

}