#pragma once
#include"./../../DoublyLinkedList/Header/DoublyLinkedList.hpp"
// #include"./../../SubscriberGroup/Header/SubscriberGroup.hpp"
class Topic{
private:
    string name;
    DoublyLinkedList queue;
public:
    Topic(string name);
    bool publish(void* data);
    string getName();
    // int getIndex();
    void* getData(string str);
    int getIndex();

};