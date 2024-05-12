#include"./../Header/DoublyLinkedList.hpp"
#include"./../../globals.h"

DoublyLinkedList::DoublyLinkedList(){

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Making a DoublyLinkedListQueue.\n"<<endl;
    }
    size = 0;
    index = 1;

    head = std::make_shared<Node>();
    tail = std::make_shared<Node>();

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Made Head and Tail Node.\n"<<endl;
    }

    head->setNext(tail);
    head->setPrev(nullptr);

    tail->setPrev(head);
    tail->setNext(nullptr);
}

bool DoublyLinkedList::add(void* data){
    std::lock_guard<mutex> guardlock(pubMutex);
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got the lock of the queue.\n"<<endl;
    }

    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    std::shared_ptr<void*> dataPtr = std::make_shared<void*>(data);
    newNode->setData(dataPtr);
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Added data to Node.\n"<<endl;
    }

    auto prev = tail->getPrev();
    auto next = tail;
    prev->setNext(newNode);
    newNode->setPrev(prev);
    newNode->setNext(tail);
    tail->setPrev(newNode);

    size+=1;
    newNode->setIndex(index);
    indexToPtrMap[index] = newNode;
    // for(auto a: indexToPtrMap){
    //     shared_ptr<Node> ptr = a.second;
    //     shared_ptr<void*> ptr2 = ptr->getData();
    //     cout<<a.first<<" "<<ptr<<" "<<ptr2<<" "<<*(int*)(*ptr2)<<endl;
    // }
    index+=1;

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Added data. size="<<size<<" index="<<index<<"\n"<<endl;
    }

}

void* DoublyLinkedList::getData(const int idx){
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Getting Data from Queue\n"<<endl;
    }
    if(indexToPtrMap.count(idx)==0){

        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"No Ptr Found\n"<<endl;
        }
        return nullptr;
    } 
    {
        void* d = *(indexToPtrMap[idx]->getData());

        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got the data "<<*(int*)d<<"\n"<<endl;
        }

        
        return d;
    }
}

void DoublyLinkedList::clearTrailingNodes(){
    int miniIndex = 10000000;
    for(auto itr: indexToPtrMap){
        int a = itr.first;
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


