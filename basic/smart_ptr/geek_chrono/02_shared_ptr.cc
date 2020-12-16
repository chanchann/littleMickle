
#include <memory>
#include <iostream>
#include <cassert> 
#include <string>

void test1() {
    using namespace std;

    shared_ptr<int> ptr1(new int(10));
    assert(*ptr1 = 10);

    shared_ptr<string> ptr2(new string("hello"));
    assert(*ptr2 == "hello");

    auto ptr3 = make_shared<int>(42);
    assert(ptr3 && *ptr3 == 42);

    auto ptr4 = make_shared<string>("zelda");
    assert(!ptr4->empty());
}


void test2() {
    using namespace std;

    auto ptr1 = make_shared<int>(42);
    assert(ptr1 && ptr1.unique() );

    auto ptr2 = ptr1;
    assert(ptr1 && ptr2);

    assert(ptr1 == ptr2);
    assert(!ptr1.unique() && ptr1.use_count() == 2);
    assert(!ptr2.unique() && ptr2.use_count() == 2);
}

int main() {
    test1();
    test2();
}