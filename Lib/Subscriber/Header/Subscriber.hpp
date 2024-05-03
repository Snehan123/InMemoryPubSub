#pragma once
#include<iostream>
#include"./../../SubscriberGroup/Header/SubscriberGroup.hpp"
using namespace std;

class Subscriber{
private:
    string name;
    shared_ptr<SubscriberGroup> ptrToGroup;
public:
    Subscriber(shared_ptr<SubscriberGroup> ptr, string name);
    void* getData();
    string getName();
};