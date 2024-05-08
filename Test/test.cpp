#include"./../Lib/InMemoryPubSub/Header/InMemoryPubSub.hpp"
#include<iostream>
#include<unistd.h>
#include<thread>
#include"./../Lib/Semaphore/Header/Semaphore.hpp"
using namespace std;

InMemoryPubSub pubSub;

class Publisher{
private:
    int time;
public:
    Publisher(int time){
        this->time  = time;
    }

    void operator()(){
        int num;
        while(true){
            cin>>num;
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

    pubSub.addTopic("Movies");
    pubSub.addSubscriberGroup("Friends","Movies");;
    
    Publisher pub(1); 
    std::thread t1(pub);

    t1.detach();

    Subs s1("Snehan",1), s2("Mohan",1), s3("Rohan",1);

    std::thread t2(s1);
    std::thread t3(s2);
    std::thread t4(s3);


    t2.join();
    t3.join();
    t4.join();
    
    return 0;

}