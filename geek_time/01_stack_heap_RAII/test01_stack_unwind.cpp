#include <stdio.h>

class Obj {
public:
    Obj() { puts("Obj()"); }
    ~Obj() { puts("~Obj()"); }
};

void foo(int n) {
    Obj obj;
    if(n == 42) 
        throw "xxx";
}

int main() {
    try { 
        foo(41);
        foo(42);
    }
    catch(const char* s) {
        puts(s);
    }
}

