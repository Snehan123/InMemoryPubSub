#include"./../Header/Node.hpp"

Node::Node(){
    data = std::make_shared<void*>();
    prev = next = std::make_shared<Node>();
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