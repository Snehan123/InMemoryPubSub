#pragma once

#include"./../../Topic/Header/Topic.h"
#include<semaphore>
using namespace std;

class SubscriberGroup{
private:
    shared_ptr<Topic> ptrToTopic;
    int index;
    counting_semaphore<int> sem;
    string name;
public:
    SubscriberGroup(string name, shared_ptr<Topic> ptr, int maxCount = 5);
    void* getData();
    // void operator()();
    string getName();
    void notify();
};