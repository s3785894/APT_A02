#include "Game.h"

Game::Game(std::string playerOneName, std::string playerTwoName){
    player1 = new Player(playerOneName);
    player2 = new Player(playerTwoName);

    gameEnd = false;
}

Game::~Game(){

}

void Game::playGame(){
    // Loop while end game condition is not met
    // For each loop, playRound(), then checkEnd()

    while (!gameEnd) {
        playRound();
        checkEnd();
    }

    // Game over
    // Finish last scoring and then determine winner
}

void Game::playGame(std::ifstream &fileInput){
    
}

void Game::playRound(){
    std::cout << "====== Start Round ======" << std::endl;

    // Logic for game round


    std::cout << "====== End Round ======" << std::endl;
}

void Game::checkEnd(){
    // Check the players board for a full horizontal row (maybe call on a function in player that does this)
    
    // if(horizontal row complete){
    //     gameEnd = true;
    // }
}