#include"./../Header/SubscriberGroup.hpp"

SubscriberGroup::SubscriberGroup(string name, shared_ptr<Topic> ptr) {
    this->name = name;
    this->ptrToTopic = ptr;
    index = 0;
}

string SubscriberGroup::getName(){
    return this->name;
}

void* SubscriberGroup::getData(){
    sem.acquire();
    return ptrToTopic->getData(name);
}

void SubscriberGroup::notify(){
    this->sem.release();
}

// void SubscriberGroup::operator()(){

// }
