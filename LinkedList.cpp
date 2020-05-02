#include "LinkedList.h"

#include <exception>
#include <iostream>
#include <fstream>

List::List() 
{
   list = new LinkedList();
   list->head = nullptr;
   list->tail = nullptr;
}

List::List(List& other) 
{
}

List::~List() {
   clear();
}

// Starting from the front (head), iterate through the list and count the amount of elements. Stop when our current node is null (meaning we have reached the end)
unsigned int List::size() {
   Node* current = list->head;
   int counter = 0;
   while (current != nullptr) {
      ++counter;
      current = current->next;
   }
   return counter;
}

char List::get(unsigned int index) {
   Node* current = list->head;

   if (index < size()) {
      int counter = 0;
      while (counter < index) {
         ++counter;
         current = current->next;
      }
   } else {
      throw std::out_of_range("Index too big");
   }

   return current->value;
}


void List::addTile(char tile) {
   Node* toAdd = new Node();
   toAdd->value = tile;
   toAdd->next = nullptr;

   if (list->head == nullptr) {
      list->head = toAdd;
   } else {
      Node* current = list->head;
      while (current->next != nullptr) {
         current = current->next;
      }
      current->next = toAdd;
   }
}

// This assumes the index is not at the front or back - can add checking for this in future
void List::addTile(char tile, unsigned int index) {
   Node* toAdd = new Node();
   Node* current = list->head;

   toAdd->value = tile;

    if (index < size()) {
      int counter = 0;
        while (counter < index) {
         ++counter;
         current = current->next;
      }
   } else {
      throw std::out_of_range("Index too big");
   }

    /*
    * Insert our node at the given index with the following steps:
    * 1. Make our previous node equal to the current's previous
    * 2. Make our next node equal to current
    * 3. Make current previous equal to our new node
    */

    toAdd->prev = current->prev;
    toAdd->next = current;
    current->prev = toAdd;
}

void List::removeTile(unsigned int index) {

}

void List::removeTileFront() {
   if (list->head != nullptr) {
      Node* toDelete = list->head;
      list->head = list->head->next;
      delete toDelete;
   } else {
      throw std::logic_error("Deleting on empty list");
   }
}

// TO-DO
void List::removeTileBack() {

}

void List::clear() {
   while (list->head != nullptr) {
      removeTileFront();
   }
}
