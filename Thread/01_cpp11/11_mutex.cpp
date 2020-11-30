/*
To fix race conditions in multi-threaded environment we need mutex 
each thread needs to lock a mutex before modifying or reading the shared data 
and after modifying the data each thread should unlock the mutex.

We need to add Lock in addMoney() method of the Wallet
Acquire lock before increment the money of Wallet and release lock before leaving that function.

mutex lock in addMoney makes sure that once one thread finishes the modification of money 
then only any other thread modifies the money in Wallet.

But what if we forgot to unlock the mutex at the end of function. 
In such scenario, one thread will exit without releasing the lock and other threads will remain in waiting

This kind of scenario can happen in case some exception came after locking the mutex. 
To avoid such scenarios we should use std::lock_guard.
*/

#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

class Wallet {
public:
    Wallet() : mMoney(0) {}
    int getMoney()   { return mMoney; }
    void addMoney(int money) {
        mutex.lock();
        for(int i = 0; i < money; ++i) {
            mMoney++;
        }
        mutex.unlock();
    }
private:
    int mMoney;
    std::mutex mutex;
};

int testMultithreadedWallet() {
    Wallet walletObject;
    std::vector<std::thread> threads;
    for(int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
    }
    for(int i = 0; i < threads.size() ; i++) {
        threads.at(i).join();
    }
    return walletObject.getMoney();
}
int main()
{
    int val = 0;
    for(int k = 0; k < 1000; k++)
    {
        if((val = testMultithreadedWallet()) != 20000)
        {
            std::cout << "Error at count = " << k << "  Money in Wallet = " << val << std::endl;
            //break;
        }
    }
    return 0;
}