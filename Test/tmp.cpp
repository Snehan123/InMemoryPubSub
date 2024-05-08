#include<iostream>
#include"./../Lib/Semaphore/Header/Semaphore.hpp"
#include<thread>
#include<unistd.h>

using namespace std;

Semaphore sem;

void fun(){
    for(int i=0;;i+=1){
        sleep(5);
        sem.release(); 
    }

}

void fun3(){
    for(int i=0;;i+=1){
        sem.acquire();
        cout<<"fun3snehan\n";
    }
}

void fun2(){
    for(int i=0;;i+=1){
        sem.acquire();
        cout<<"fun2 snehan\n";
    }
}

int main(){
    // return 0;
    thread t1(fun);
    thread t2(fun2);
    thread t3(fun3);

    scanf("\n");
    return 0;   
}