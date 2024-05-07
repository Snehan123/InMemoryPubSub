#pragma once
#include"Node.hpp"
#include<map>
#include<mutex>
using namespace std;

class DoublyLinkedList{
private:
    std::shared_ptr<Node> head, tail;
    int size; 
    map<int,shared_ptr<Node>> indexToPtrMap;
    std::mutex pubMutex;
    map<string,int> groupToIndex;
    int index;
public:
    DoublyLinkedList();
    bool add(void* data);
    void* getData(std::string str);
    bool pop();
    int getCurrMinIndex();
};