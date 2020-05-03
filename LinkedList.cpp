#include "LinkedList.h"
#include <exception>
#include <iostream>
#include <fstream>

    Node::Node(TileCode tile, Node* next) {
    if (tile == R) {
      this->tileValue = 'R';
   } else if (tile == Y) {
      this->tileValue = 'Y';
   } else if (tile == B) {
      this->tileValue = 'B';
   } else if (tile == L) {
      this->tileValue = 'L';
   } else if (tile == U) {
      this->tileValue = 'U';
   }            
   this->next=next;
}
   LinkedList::LinkedList(){
       head=nullptr;
       tail=nullptr;
       listSize=0;
   }
   LinkedList::~LinkedList(){
       clear();
   }
   unsigned int LinkedList::size(){
       return listSize;
   }

   void LinkedList::clear(){
       while (head != nullptr) {
        removeFront();
        }
   }

    void LinkedList::removeBack(){
        if(tail!=nullptr){
            Node* current = head;
            while (current->next->next !=nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next=nullptr;
            listSize--;
        } 
    }
    void LinkedList::removeFront(){
            if(head!=nullptr){
                Node* current = head;
                Node* nextNode = current->next;
                head=nextNode;
                delete current;
                listSize--;
        } 
    }

    void LinkedList::printList() const{
        Node* current = head;
        while (current != nullptr) {
            std::cout<<current->tileValue<<" ";
            current = current->next;
        }
        std::cout<<std::endl;
   }
   char LinkedList::get(unsigned int i){
       Node* current =head;
       for(int j = 0; j<i;++j){
           current=current->next;
       }
       return current->tileValue;
   }

   void LinkedList::addFront(TileCode tile){
       Node* node = new Node(tile,nullptr);
       if (head==nullptr){
           head=node;
           tail=node;
       }else{
           node->next=head;
           head=node;
       }
        listSize++;


   }
   void LinkedList::addBack(TileCode tile){
        Node* node = new Node(tile,nullptr);
       if (head==nullptr){
           head=node;
           tail=node;

       }else{
           tail->next=node;
           tail=node;
       }
        listSize++;


   }