#pragma once
#include"Node.hpp"
#include<map>

class DoublyLinkedList{
private:
    std::shared_ptr<Node> head, tail;
    int size; 
    int index;
    std::unordered_map<int,std::shared_ptr<Node>> indexToPtrMap;
public:
    DoublyLinkedList(){
        size = 0;
        head = std::make_shared<Node>();
        tail = std::make_shared<Node>();

        head->setNext(tail);
        head->setPrev(nullptr);

        tail->setPrev(head);
        tail->setNext(nullptr);
    }

    bool add(void* data);
    void* getData(int index);
    void pop();
    int getCurrMinIndex();
};