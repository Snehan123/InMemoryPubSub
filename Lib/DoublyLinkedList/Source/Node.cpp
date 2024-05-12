#include"./../Header/Node.hpp"
#include"./../../globals.h"
using namespace std;
Node::Node(){
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Making a node\n"<<endl;
    }
    data = std::make_shared<void*>();
}

void Node::setData(std::shared_ptr<void*> data){
    this->data = data;
}

std::shared_ptr<void*> Node::getData(){
    return this->data;
}

std::shared_ptr<Node> Node::getNext(){
    return next;
}

std::shared_ptr<Node> Node::getPrev(){
    return prev;
}

void Node::setPrev(std::shared_ptr<Node> ptr){
    this->prev = ptr;
}

void Node::setNext(std::shared_ptr<Node> ptr){
    this->next = ptr;
}

int Node::getIndex(){
    return index;
}

void Node::setIndex(int idx){
    this->index = idx;
}