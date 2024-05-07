#include"./../Header/Topic.h"

Topic::Topic(string name){
    this->name = name;
}

string Topic::getName(){
    return this->name;
}

bool Topic::publish(void* data){

    return queue.add(data);
}

// int Topic::getIndex(){
//     return queue.getCurrMinIndex();
// }

void* Topic::getData(string str){
    queue.getData(str);
}