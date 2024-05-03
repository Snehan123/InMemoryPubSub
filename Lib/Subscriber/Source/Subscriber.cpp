#include"./../Header/Subscriber.hpp"

Subscriber::Subscriber(shared_ptr<SubscriberGroup> ptr, string name){
    ptrToGroup = ptr;
    this->name = name;
}

string Subscriber::getName(){
    return this->name;
}

void* Subscriber::getData(){
    return ptrToGroup->getData();
}