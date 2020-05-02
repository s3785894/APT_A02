#include "Player.h"

Player::Player(std::string name){
    this->name = name;
}

Player::~Player(){

}

std::string Player::getName(){
    return name;
}

int Player::getScore(){
    //score = board->calculateScore;
    //return score;
}