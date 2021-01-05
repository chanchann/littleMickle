/*
Reference member variables as class members

https://stackoverflow.com/questions/12387239/reference-member-variables-as-class-members


*/

#include <iostream>
using namespace std;

class Agg {
public:
    Agg() = default;
    Agg(int a) : _a(a) {}
    int getA() const { return _a; }
private:
    int _a = 1;
};

class Foo {
public:
   Foo(Agg& agg) : _agg(agg) {}
   void print() { cout << _agg.getA() << endl; }
private:
   const Agg& _agg; 
};


int main(int argc, char* argv[]) {
    Agg agg(5);
    Foo foo(agg);
    foo.print();
    return 0;
}