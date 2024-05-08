#pragma once

#include"./../../Topic/Header/Topic.h"
#include"./../../Semaphore/Header/Semaphore.hpp"
#include<semaphore>
#include<thread>
using namespace std;

class SubscriberGroup{
private:
    shared_ptr<Topic> ptrToTopic;
    int index;
    Semaphore sem;
    string name;
public:
    SubscriberGroup(string name, shared_ptr<Topic> ptr);
    void* getData();
    // void operator()();
    string getName();
    void notify();
};