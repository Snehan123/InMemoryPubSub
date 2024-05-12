#include"./../Lib/InMemoryPubSub/Header/InMemoryPubSub.hpp"
#include<iostream>
#include<unistd.h>
#include<thread>
#include"./../Lib/Semaphore/Header/Semaphore.hpp"
#include"./../Lib/globals.h"
#include<memory>
using namespace std;

InMemoryPubSub pubSub;

class Publisher{
private:
    int time;
public:
    Publisher(int time){
        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Publisher Made with time "<<time<<"\n"<<endl;
        }
        this->time  = time;
    }

    void operator()(){
        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Starting Publisher Loop\n"<<endl;
        }
        int num;
        while(true){
            cin>>num;
            if(debug){
                cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Publisher publishing "<<num<<"\n"<<endl;
            }
            pubSub.publish("Movies",(void*)&num);
        }
    }

};

class Subs{
private:
    shared_ptr<Subscriber> ptr;
    string name;
    int time;
public:
    Subs(string name, int time){
        this->name  = name;
        this->time = time;
        ptr = pubSub.addSubscriber("Friends",name);
    }

    void operator()(){

        while(true){
            void* a = ptr->getData();
            int b = *(int*)a;
            cout<<b<<" "<<name<<endl;;
            sleep(time);
        }
    }

};


int main(){
    // counting_semaphore<10> sem(0);
    Semaphore sem;
    // string sp = "abv"; 
    // shared_ptr<Topic> ptr = make_shared<Topic>();
    // return 0;

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Made Semaphore\n"<<endl;
    }
    pubSub.addTopic("Movies");
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Added Topic\n"<<endl;
    }
    pubSub.addSubscriberGroup("Friends","Movies");;
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Added Subscriber Group\n"<<endl;
    }
    Publisher pub(1); 
    std::thread t1(pub);

    // t1.detach();

    // Subs s1("Snehan",1), s2("Mohan",1), s3("Rohan",1);

    // std::thread t2(s1);
    // std::thread t3(s2);
    // std::thread t4(s3);


    // t2.join();
    // t3.join();
    // t4.join();
    t1.join();
    // while(true){;}
    
    return 0;

}