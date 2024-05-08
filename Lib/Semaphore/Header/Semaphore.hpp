#pragma once
using namespace std;
#include<mutex>
#include<condition_variable>

class Semaphore{
private:
    int cnt;
    mutex mtx;
    condition_variable cv;
public:
    Semaphore();
    void release();
    void acquire();
};