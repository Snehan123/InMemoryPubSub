#pragma once
#include<iostream>


class Node{
private:
    std::shared_ptr<void*> data;
    std::shared_ptr<Node> prev, next;
    int readCount;
public:
    Node();
    void setData();
    std::shared_ptr<void*> getData();
    std::shared_ptr<Node> getNext();
    std::shared_ptr<Node> getPrev();
    void setPrev(std::shared_ptr<Node> ptr);
    void setNext(std::shared_ptr<Node> ptr);
};