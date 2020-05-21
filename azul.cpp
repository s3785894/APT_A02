#include <iostream>
#include <fstream>
#include <exception>
#include <limits>

#include "Types.h"
#include "Bag.h"
#include "Game.h"

// Displays menu and processes initial input
int displayMenu();

// Prints credits (called from menu)
void printCredits();

// Creates and initiates new game (called from menu)
void newGame(std::string seed, bool hasSeeded);

// Loads saved game from file (called from menu)
void loadGame();

// Provides game explanation (called from menu)
void howTo();

// Processes command line argument for potential seeded game
void processArgs(int argc, char **argv, std::string *seed, bool *hasSeeded);

int main(int argc, char **argv)
{
    std::string *seed = new std::string;
    bool *hasSeeded = new bool(false);
    processArgs(argc, argv, seed, hasSeeded);

    bool exit = false;

    while (!exit)
    {
        int mode = displayMenu();

        if (mode == 1)
        {
            // Start a new game either with a default (random) seed or with a seed provided by the user
            newGame(*seed, *hasSeeded);
        }
        else if (mode == 2)
        {
            // Load a game from a save file
            loadGame();
        }
        else if (mode == 3)
        {
            // Show student credits
            printCredits();
        }
        else if (mode == 4)
        {
            // Basic information on how to use the program
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

    int input;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "> ";
        std::cin >> input;

        if (std::cin.good())
        {
            if (input > 0 && input <= 5)
            {
                validInput = true;
            }
            else
            {
                std::cout << "Invalid menu selection. Please enter the number preceeding any of the menu options above." << std::endl;
            }
        }
        else if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Please only enter a single integer between 1 and 5." << std::endl;
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

void newGame(std::string seed, bool hasSeeded)
{
    std::string playerOneName;
    std::string playerTwoName;

    std::cout << "Enter name for Player 1: " << std::endl;
    std::cin >> playerOneName;

    std::cout << "Enter name for Player 2: " << std::endl;
    std::cin >> playerTwoName;

    std::unique_ptr<Game> game(new Game(playerOneName, playerTwoName, seed, hasSeeded));
    // Loads game (with parameter isMidRound as boolean value false, as this is a new game)
    game->playGame(false);
}

void loadGame()
{
    std::cout << "Enter the filename from which to load the game" << std::endl;
    try
    {
        std::cout << "> ";
        std::string filename;
        std::cin >> filename;

        std::ifstream fileInput;
        fileInput.open(filename);

        // Throws an exception if the file cannot be located (i.e. bad file input)
        if (!fileInput.good())
        {
            throw std::exception();
        }

        // Passes refrence to file input object into game object for processing the input file
        std::unique_ptr<Game> game(new Game(fileInput));
        game->playGame(true);
    }
    catch (std::exception e)
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
        When playing the game, the input for a turn is in the format of 'turn [FACTORY] [TILE] [PATTERN LINE]'. There should be spaces inbetween each word/number. \n \
        \n \
        For example, if you want to take all the blue tiles from factory 2, and place them in your 3rd pattern line, the input would be: \n \
        turn 2 B 3 \n \
        \n \
        Type 'mosaic' at any time during a players turn if you wish to view the structure of the mosaic (where each tile goes on the mosaic) \n \
        \n \
        If at any point you would like to save your game, type 'save [FILENAME]'. This will save the game in it's current state and then\n \
        continue the current turn\n \
        \n \
        To exit the game, type 'exit'. This will exit WITHOUT saving.\n \
        \n \
        All inputs are not case sensitive so they will work no matter how you type them.\n \
        ";

    std::cout << string << std::endl;
}

void processArgs(int argc, char **argv, std::string *seed, bool *hasSeeded)
{
    // If the command line has three arguments, this means that the third argument must be the seed
    if (argc == 3)
    {
        // Take the seed
        *seed = argv[2];
        *hasSeeded = true;
    }
}