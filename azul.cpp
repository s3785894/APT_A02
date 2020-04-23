#include <iostream>

#include "Types.h"

int displayMenu();
void prntCredits();

int main(void)
{
    int mode = displayMenu();
    if (mode == 1)
    {
        // new game
    }
    else if (mode == 2)
    {
        // load game
    }
    else if (mode == 3)
    {
        prntCredits();
    }
    else if (mode == 4)
    {
        std::cout << "Exiting Program!" << std::endl;
        return EXIT_SUCCESS;
    }
}

int displayMenu()
{
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Menu" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;

    int input = -1;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "> ";
        if (std::cin.good())
        {
            std::cin >> input;
            if (input > 0 && input <= 4)
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

void prntCredits(){
    std::cout << "Student 1:" << std::endl;
    std::cout << STUDENT_ONE << std::endl << std::endl;

    std::cout << "Student 2:" << std::endl;
    std::cout << STUDENT_TWO << std::endl << std::endl;

    std::cout << "Student 3:" << std::endl;
    std::cout << STUDENT_THREE << std::endl << std::endl;
}