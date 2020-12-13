/*
 A function that returns while a thread still has access to local variables

If you don’t wait for your thread to finish, you need to ensure that the data
accessed by the thread is valid until the thread has finished with it

One situation in which you can encounter such problems is when the thread function holds pointers or references to local variables and the thread hasn’t finished
when the function exits

In this case, the new thread associated with my_thread will probably still be running
when oops exits, because you’ve explicitly decided not to wait for it by calling detach().

One common way to handle this scenario is to make the thread function self-contained
and copy the data into the thread rather than sharing the data. If you use a callable
object for your thread function, that object is copied into the thread, so the original
object can be destroyed immediately. But you still need to be wary of objects containing pointers or references, such as in listing 2.1. In particular, it’s a bad idea to create
a thread within a function that has access to the local variables in that function, unless
the thread is guaranteed to finish before the function exits.
Alternatively, you can ensure that the thread has completed execution before the
function exits by joining with the thread.
*/

#include <thread>
#include <iostream>

void do_something(int& i) {
    ++i;
}

struct func {
    // int& i;
    int i;

    func(int& i_):i(i_){}

    void operator()() {
        for(unsigned j=0; j < 1000000; ++j) {
            do_something(i);
        }
    }
};

void oops() {
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main() {
    oops();
}
