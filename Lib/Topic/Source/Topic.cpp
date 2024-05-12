#include"./../Header/Topic.h"
#include"./../../globals.h"
Topic::Topic(string name){
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Creating a new Topic\n"<<endl;
    }
    this->name = name;
}

string Topic::getName(){
    return this->name;
}

bool Topic::publish(void* data){
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Topic adding Data\n"<<endl;
    }
    return queue.add(data);
}

// int Topic::getIndex(){
//     return queue.getCurrMinIndex();
// }

void* Topic::getData(string str){
    queue.getData(str);
}