#pragma once
#include"./../../DoublyLinkedList/Header/DoublyLinkedList.hpp"
#include<memory>
// #include"./../../SubscriberGroup/Header/SubscriberGroup.hpp"
class Topic{
private:
    string name;
    DoublyLinkedList queue;
    map<string,int> subscriberGroupToIndex;
public:
    Topic(string name);
    bool publish(void* data);
    string getName();
    // int getIndex();
    void* getData(string str);

    void registerSubscriberGroup(string name);
    // int getIndex();

};