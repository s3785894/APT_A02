#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
   // Constructor
   LinkedList();

   // Deconstructor
   ~LinkedList();
   
   // Returns the list size
   unsigned int size();

   // Remove all nodes from list
   void clear();

   // Get char representation of tile at given index
   char get(unsigned int i);

   // Add tile to front of the list
   void addFront(char tile);

   // Add tile to back of the list
   void addBack(char tile);

   // Remove tile from back of the list
   void removeBack();
   
   // Remove tile from front of the list
   void removeFront();

   //print all nodes in the list
   void printList() const;

private:
   Node* head;
   Node* tail;
   int listSize;

};

#endif // LINKED_LIST_H