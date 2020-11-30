/*
Now Let’s create 5 threads and all these threads will share a same object of class Wallet 
and add 1000 to internal money using it’s addMoney() member function in parallel.
So, if initially money in wallet is 0. 
Then after completion of all thread’s execution money in Wallet should be 5000.

But, as all threads are modifying the shared data at same time, 
it might be possible that in some scenarios money in wallet at end will be much lesser than 5000.

但是这里并没有出现这种情况？？？What happens?

当我创建20个进程时出现问题。

mMoney++:

Load “mMoney” variable value in Register
Increment register’s value
Update variable “mMoney” with register’s value

How to fix this?
*/


#include <iostream>
#include <vector>
#include <thread>
class Wallet {
public:
    Wallet() : mMoney(0){}
    int getMoney() { return mMoney; }
    void addMoney(int money) {
       for(int i = 0; i < money; ++i) {
          mMoney++;
       }
    }
private:
    int mMoney;
};

int testMultithreadedWallet() {
   Wallet walletObject;
   std::vector<std::thread> threads;
   for(int i = 0; i < 20; ++i){
        threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
   }
   for(int i = 0; i < threads.size() ; i++) {
       threads.at(i).join();
   }
   return walletObject.getMoney();
}

int main() {
  int val = 0;
  for(int k = 0; k < 1000; k++) {
    if((val = testMultithreadedWallet()) != 20000) {
    std::cout << "Error at count = " << k << " Money in Wallet = " << val << std::endl;
    }
    // std::cout << val << std::endl;
  }
  return 0;
}