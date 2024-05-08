#include"./../Header/Semaphore.hpp"

Semaphore::Semaphore(){
    cnt=0;
}

void Semaphore::release(){
    lock_guard<mutex> grd(mtx);
    cnt+=1;
    cv.notify_one();
}

void Semaphore::acquire(){

    unique_lock<mutex> lock(mtx);

    if(cnt==0){
        while(cnt==0){
            cv.wait(lock);
        }
    }

    cnt--;
    
}