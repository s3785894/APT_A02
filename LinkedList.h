#ifndef LIST_H
#define LIST_H 

#include <istream>
#include <string>
#include <vector>

class Node {
public:
   char value; //Tile value
   Node* next; //Pointer to next node
   Node* prev; //Pointer to previous node
};

class LinkedList {
public:
   Node* head;
   Node* tail;
};

// Represents a list of Tiles. Terminology is purposely kept generic so that a list can be used in multiple places if required
class List {
public:
   List();
   List(List& other);
   ~List();

// Return the current size of the List
   unsigned int size();

// Get a tile at the given index (likely to not be used - can possible remove in future)
   char get(unsigned int index);

// Add a tile to the back of the list
   void addTile(char tile);

// Add a tile in the given spot (likely to not be used - can possibly remove in future)
   void addTile(char tile, unsigned int index);

// Remove a tile in the given spot (likely to not be used - can possibly remove in future)
   void removeTile(unsigned int index);

// Remove a tile from the front of the list
   void removeTileFront();

// Remove a tile from the back of the list
   void removeTileBack();

// Remove's all tiles from the list
   void clear();

private:
   LinkedList* list;
};

#endif
