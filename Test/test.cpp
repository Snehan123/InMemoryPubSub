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

        vector<int> v;
        int num;
        while(true){
            cin>>num;
            v.push_back(num);
            if(debug){
                cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Publisher publishing "<<num<<"\n"<<endl;
            }
            pubSub.publish("Movies",(void*)&v[v.size()-1]);
        }
    }

};

class Subs{
private:
    shared_ptr<Subscriber> ptr;
    string name;
    int time;
    string subsGroup;
public:
    Subs(string name,string subsGroup, int time){
        this->name  = name;
        this->time = time;
        this->subsGroup = subsGroup;
        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Created a subscriber. Adding it to the subscriber group \n"<<endl;
        }
        ptr = pubSub.addSubscriber(name,subsGroup);
        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got the ptr to subscriber in the subsriber.\n"<<endl;
        }   
    }

    void operator()(){

        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Starting loop for subscriber\n"<<endl;
        }

        while(true){
            void* a = ptr->getData();
            int b = *(int*)a;
            cout<<" Name:"<<name<<" Data:"<<b<<endl;;
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
    pubSub.addSubscriberGroup("Friends&Friends","Movies");;
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Added Subscriber Group\n"<<endl;
    }

    Publisher pub(1); 
    std::thread t1(pub);

    // t1.detach();

    Subs s1("Snehan","Friends",5), s2("Mohan","Friends",10), s3("Rohan","Friends",15);
    Subs s4("Snehan2","Friends&Friends",5), s5("Mohan2","Friends&Friends",10), s6("Rohan2","Friends&Friends",15);

    std::thread t2(s1);
    std::thread t3(s2);
    std::thread t4(s3);

    std::thread t5(s4);
    std::thread t6(s5);
    std::thread t7(s6);


    // t2.join();
    // t3.join();
    // t4.join();
    t1.join();
    // while(true){;}
    
    return 0;

}