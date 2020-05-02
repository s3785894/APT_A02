#include "Table.h"
#include <iostream>

Table::Table(){
    bag = new Bag();
}

Table::~Table(){
    delete bag;
}

void Table::takeTiles(int factory, char tileColour, Player &player){

}

void Table::initialiseRound() {
    // Put the first player token in the table centre
    tableCentre.insert(tableCentre.begin(), 'F');

    // Fill our factories from our bag of tiles
    for (int factory = 0; factory < NUM_FACTORIES; factory++){
        for (int column = 0; column < FACTORY_SIZE; column++){
            factories[factory][column] = bag->grabTile();
        }
    }
}

bool Table::tilesLeft(){
    bool tilesLeft;

    /*
    * if (tableCentre.empty() || (iterate  through factory array and check if tiles are there)) {
    *   tilesLeft = false;
    * } else {
    *   tilesLeft = true;
    * }
    */ 

    return tilesLeft;
}

void Table::printFactoryContents(){
    std::cout << "Factories:" << std::endl;
    
    // First print our table centre as 'factory 0'
    std::cout << "0:" << std::endl;
    for (int i = 0; i < tableCentre.size(); i++){
        std::cout << tableCentre.at(i) << " ";
    }

    // Then print our array containing our tile factories
    for (int factory = 0; factory < NUM_FACTORIES; factory++) {
        std::cout << factory + 1 << ": ";

        // Iterate through the current factory and print each element, seperated by a space
        for (int column = 0; column < FACTORY_SIZE; column++){
            std::cout << factories[factory][column] << " ";
        }

        // Go to next line after all tiles in a factory are printed
        std::cout << std::endl; 
    }

}