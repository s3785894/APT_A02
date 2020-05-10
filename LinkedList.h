#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//#include "Tile.h"

 enum TileCode{
    R,
    Y, 
    B, 
    L, 
    U
};
class Node {
public:
   //Node(Tile* tile, Node* next);
   Node(char tile, Node* next);

   char getTile();
   char tileValue;
   Node* next;
};	
class LinkedList {
public:
   LinkedList();
   ~LinkedList();
   
   //return list size
   unsigned int size();

   //remove all nodes from list
   void clear();

   //get string representation of tile at given index
   char get(unsigned int i);

   //add tile to front of the list
   void addFront(char tile);

   //add tile to back of the list
   void addBack(char tile);

   //remove tile from back of the list
   void removeBack();
   //remove tile from front of the list
   void removeFront();

   //print all nodes in the list
   void printList() const;

private:
   Node* head;
   Node* tail;
   int listSize;

};

#endif // LINKED_LIST_H