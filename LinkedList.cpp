#include "LinkedList.h"
#include <exception>
#include <iostream>
#include <fstream>

    Node::Node(char tile, Node* next) {

    this->tileValue = tile;         
    this->next=next;
}
   LinkedList::LinkedList(){
       head=nullptr;
       tail=nullptr;
       listSize=0;
   }

   //clear the linked list first before destorying
   LinkedList::~LinkedList(){
       clear();
   }
   unsigned int LinkedList::size(){
       return listSize;
   }
//remove from front of the list until empty
   void LinkedList::clear(){
       while (head != nullptr) {
        removeFront();
        }
   }


    void LinkedList::removeBack(){
    //if one node is in the LinkedList, set head and tail to nullptr. ListSize becomes 0
    //else set current node to the node before the last node, delete the last node and set current node to tail
        if(listSize==1){
            head=nullptr;
            tail=nullptr;
            listSize=0;
        }else if(tail!=nullptr){
            Node* current = head;
            while (current->next->next !=nullptr) {
                current = current->next;
            }
            delete current->next;
            tail=current;
            current->next=nullptr;
            listSize--;
    //if one node is in the list, the head and tail points to the same address
            if(listSize==1){
                head=tail;
            }
        } 
    }

    /*
    Remove from front of the linked list:
    current node pointer points to head and next node is the next node of current node
    head points to the second node in the list and the current node which is the first node of the list is deleted
    if head is nullptr, there is no nodes in the list and tail would also be nullptr
    */
    void LinkedList::removeFront(){
            if(head!=nullptr){
                Node* current = head;
                head=head->next;
                delete current;
                listSize--;
                if(head==nullptr){
                    tail=nullptr;
                }
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
       //find node at given index i, if i is larger than listSize throw exception
        Node* current =head;
        if (i < listSize) {
            int counter = 0;
            while (counter < i) {
                ++counter;
                current = current->next;
            }
        } else if (i > listSize){
            throw std::out_of_range("Index too big");
        }
       return current->tileValue;
   }

   void LinkedList::addFront(char tile){
       Node* node = new Node(tile,nullptr);
       if (head==nullptr){
           head=node;
           tail=node;
       }else{
           //the next node points to head and the head is now the node added at the front
           node->next=head;
           head=node;
       }
        listSize++;


   }

   void LinkedList::addBack(char tile){
        Node* node = new Node(tile,nullptr);
        //if no nodes are in the list, head and pointer points to new node
       if (head==nullptr){
           head=node;
           tail=node;

       }else{
        //otherwise, set the next node of tail to new node, and move tail pointer to new node
           tail->next=node;
           tail=node;
       }
        listSize++;


   }