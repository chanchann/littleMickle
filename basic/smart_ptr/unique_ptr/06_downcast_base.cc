/*
Downcast unique_ptr to access a function [duplicate]

https://stackoverflow.com/questions/22946223/downcast-unique-ptr-to-access-a-function

std::unique_ptr with derived class

https://stackoverflow.com/questions/17417848/stdunique-ptr-with-derived-class

“Downcasting” unique_ptr<Base> to unique_ptr<Derived>

https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived
*/

#include <iostream> 
#include <vector>
#include <memory>
using namespace std;

class Base {
public:   
    void foobar() { cout << "foobar"; }
};

class Derived : public Base {
public:
    void print() { cout << "hello world!"; }
};

int main(int argc, char *argv[]) 
{
    vector<unique_ptr<Base>> bases;
    bases.push_back(unique_ptr<Base> (new Derived()));

    //ok
    bases[0]->foobar();
    //error
    //how can I make this works?
    // static_cast<Derived*> (bases[0])->print();



    return 0;
}