#include"./../Header/DoublyLinkedList.hpp"

DoublyLinkedList::DoublyLinkedList(){
    size = 0;
    index = 0;

    head = std::make_shared<Node>();
    tail = std::make_shared<Node>();

    head->setNext(tail);
    head->setPrev(nullptr);

    tail->setPrev(head);
    tail->setNext(nullptr);
}

bool DoublyLinkedList::add(void* data){
    std::lock_guard<mutex> guardlock(pubMutex);

    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->setIndex(index);
    std::shared_ptr<void*> dataPtr = std::make_shared<void*>();
    newNode->setData(dataPtr);

    auto prev = tail->getPrev();
    auto next = tail;
    prev->setNext(newNode);
    newNode->setPrev(prev);
    newNode->setNext(tail);
    tail->setPrev(newNode);

    size+=1;
    indexToPtrMap[index] = newNode;
    index+=1;

}

void* DoublyLinkedList::getData(std::string str){
    if(groupToIndex.count(str)==0){
        return nullptr;
    }else{
        int index = groupToIndex[str];
        auto d = *(indexToPtrMap[index]->getData());
        groupToIndex[str]+=1;



        int miniIndex = 10000000;
        for(auto itr: groupToIndex){
            int a = itr.second;
            miniIndex = std::min(miniIndex,a);
        }
        auto tmp = head->getNext();
        auto prev = head;
        while(tmp!=tail){
            if(miniIndex > tmp->getIndex()){
                prev->setNext(tmp->getNext());
                tmp->setPrev(prev);
            }
            prev = tmp;
            tmp = tmp->getNext();
        }
        return d;
    }
}

bool DoublyLinkedList::pop(){
    if(size==0)return false;

    auto prev = head, next = head->getNext();
    prev->setNext(next);
    next->setPrev(head);
    size-=1;
    index+=1;
}

int DoublyLinkedList::getCurrMinIndex(){
    return index;
}


