/*
std::lock_guard is a class template, which implements the RAII for mutex.
It wraps the mutex inside it’s object and locks the attached mutex in its constructor. 
When it’s destructor is called it releases the mutex.

*/
#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

class Wallet {
public:
    Wallet() : mMoney(0) {}
    int getMoney() { return mMoney; }
    void addMoney(int money) {
        std::lock_guard<std::mutex> lockGuard(mutex);
        // In constructor it locks the mutex
        for(int i = 0; i < money; ++i) {
            // If some exception occurs at this
            // poin then destructor of lockGuard
            // will be called due to stack unwinding.
            //
            mMoney++;
        }
        // Once function exits, then destructor
        // of lockGuard Object will be called.
        // In destructor it unlocks the mutex.
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