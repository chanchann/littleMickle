## Thread



## What std::thread accepts in constructor ?

We can attach a callback with the std::thread object, that will be executed when this new thread starts. These callbacks can be,

1. Function Pointer
2. Function Objects
3. Lambda functions

```cpp
std::thread thObj(<CALLBACK>);
```

## Differentiating between threads

```cpp
std::thread::get_id()

std::this_thread::get_id()
```

If std::thread object does not have an associated thread then get_id() will return a default constructed std::thread::id object i.e. not any thread.

std::thread::id is an Object, it can be compared and printed on console too

## Joining and Detaching Threads

Once a thread is started then another thread can wait for this new thread to finish. For this another need to call join() function on the std::thread object i.e.

```cpp
std::thread th(funcPtr);
// Some Code
th.join();
```

bind : https://elloop.github.io/c++/2015-12-21/learning-using-stl-23-std-mem-fn

Detaching Threads using std::thread::detach()

```cpp
std::thread th(funcPtr);
th.detach();
```

After calling detach(), std::thread object is no longer associated with the actual thread of execution.

### Be careful with calling detach() and join() on Thread Handles

Case 1: Never call join() or detach() on std::thread object with no associated executing thread

```cpp
std::thread threadObj( (WorkerThread()) );
threadObj.join();
threadObj.join(); // It will cause Program to Terminate

// or
std::thread threadObj( (WorkerThread()) );
threadObj.detach();
threadObj.detach(); // It will cause Program to Terminate
```

Therefore, before calling join() or detach() we should check if thread is join-able every time i.e.

Case 2 : Never forget to call either join or detach on a std::thread object with associated executing thread

Because inside the destructor it checks if Thread is Still Join-able then Terminate the program。

Similarly we should not forget call either join() or detach() in case of exceptions. To prevents with we should use RAII i.e.

## Carefully Pass Arguments to Threads

case 1 : Don’t pass addresses of variables from local stack to thread’s callback function

Because it might be possible that local variable in Thread 1 goes out of scope but Thread 2 is still trying to access it through it’s address

case 2: Similarly be careful while passing pointer to memory located on heap to thread. Because it might be possible that some thread deletes that memory before new thread tries to access it.

### pass references 

As arguments are copied to new threads stack so, if you need to pass references in common way i.e.

Even if threadCallback accepts arguments as reference but still changes done it are not visible outside the thread.

Its because x in the thread function threadCallback is reference to the temporary value copied at the new thread’s stack.

```cpp
//How to fix this ?

std::ref() 
```
### Assigning pointer to member function of a class as thread function:

Pass the pointer to member function as callback function and pass pointer to Object as second argument.

## Part 4: Data Sharing and Race Conditions

race condition : When two or more threads perform a set of operations in parallel, that access the same memory location.  Also, one or more thread out of them modifies the data in that memory location, then this can lead to an unexpected results some times.

## Part 5: Using mutex to fix Race Conditions

## Part 6: Need of Event Handling

## Part 7: Condition Variables Explained