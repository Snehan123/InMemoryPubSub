#include"./../Header/SubscriberGroup.hpp"

SubscriberGroup::SubscriberGroup(string name, shared_ptr<Topic> ptr,int maxCount = 5) : sem(0){
    this->name = name;
    this->ptrToTopic = ptr;
    index = ptrToTopic->getIndex();
}

string SubscriberGroup::getName(){
    return this->name;
}

void* SubscriberGroup::getData(){
    sem.acquire();
    return ptrToTopic->getData(index++);
}

void SubscriberGroup::notify(){
    this->sem.release();
}

// void SubscriberGroup::operator()(){

// }
