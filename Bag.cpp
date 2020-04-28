#include "Bag.h"
#include <iostream>
#include <vector>

Bag::Bag(){
    fillBag();
}

Bag::~Bag(){

}

void Bag::viewContents(){

}

void Bag::fillBag(){
    //Fill the bag with our tiles, number of tiles per colour is determined by the max amount of tiles / the number of colours (even split)
    for(int i = 0; i < NUM_COLOURS; i++){

            /*
            *   The for loop will loop as many times as there are different tiles
            *   
            *   The syntax for insert() is (position, amount, value)
            *   So what we have is (at end of our vector, insert an amount of tiles based on the calculation (20), insert the char at the index of the array that holds our possible tile colours)
            */
            bag.insert(bag.end(), (MAX_TILES / NUM_COLOURS), tileColours[i]);
    }

    //Once our bag is filled with our tiles, we need to shuffle it
    shuffleBag();
}

void Bag::shuffleBag(){
	int size = bag.size();
    //Set the seed based on the current system time to ensure a different seed every tme
    srand (time (0));

    //Loops through each element of the vector
	for (int i = 0; i < size - 1; i++)
	{
        //Generate a random number, j, in the range of our vector size
		int j = i + rand() % (size - i);

        //Swap the tile at index j with the tile at the current index i
		std::swap(bag[i], bag[j]);
	}
}

char Bag::grabTile(){
    //Since our bag is always randomly shuffled at the start, to grab random tiles we can grab tiles from the front of the bag
    char tile = bag.front();

    //Remove this tile from the bag (Erase the first tile in the vector, which is the tile we've grabbed)
    bag.erase(bag.begin());

    //Return our tile
    return tile;
}