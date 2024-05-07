#pragma once
#include<iostream>
#include<mutex>

class Node{
private:
    std::shared_ptr<void*> data;
    std::shared_ptr<Node> prev, next;
    int index;
public:
    Node();
    void setData(std::shared_ptr<void*> data);
    std::shared_ptr<void*> getData();
    std::shared_ptr<Node> getNext();
    std::shared_ptr<Node> getPrev();
    void setPrev(std::shared_ptr<Node> ptr);
    void setNext(std::shared_ptr<Node> ptr);
    int getIndex();
    void setIndex(int index);
};