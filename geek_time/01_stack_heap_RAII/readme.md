## 01 stack / heap / RAII : cpp resources management

## Basic concept 

### heap 

new / delete -> free store 

malloc / free -> heap

`free store` is the subspace of `heap`

```cpp
auto ptr = new std::vector<int>();
```

Memory leak

```cpp
void foo() {
    bar* ptr = new bar();
    ...
    delete ptr;
}
```

Here are two problems:

1. Maybe it may throw an exception before delete action which Causes this operation to not be executed.

2. Don't write cpp like this. In this situation, we use stack rather than heap.

Normally, new and delete are not in the same function.

```cpp
bar* make_bar() {
    bar* ptr = nullptr;
    try{
        ptr = new bar();
        ....
    }
    catch(...) {
        delete ptr;
        throw;
    }
    return ptr;
}

void foo() {
    ...
    bar* ptr = make_bar();
    ...
    delete ptr;
}
```

### stack

stack unwinding: 

The Compiler will automatically call the destructor. When an exception occurs, we call the destructor, this process is stack unwinding.

```cpp
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
```

```
Obj()
~Obj()
Obj()
~Obj()
xxx
```

The result shows that no matter whether the exception occurs, the destructor will be executed.


### RAII 

Resources Acquisition is Initializaiton.

c++ support that we can store objects on the stack.

But in many cases, objects can't or shouldn't store on the stack because:

1. The object is large

2. The size of object is not sure when compiling

3. object is the return value of the function. Due to some special reason, we shouldn't return the value of the object

For example: a factory method instance, the return value is base class('s ptr or reference)

```cpp
enum class shape_type {
    circle,
    triangle,
    rectangle,
    ...
};

class shape { ... };
class circle : public shape { ... };
class triangle : public shape { ... };
class rectangle : public shape { ... };

shape* create_shape(shape_type type) {
    ...
    swtich(type) {
        case shape_type::circle:
            return new circle(...);
        case shape_type::triangle:
            return new triangle(...);
        case shape_type::rectangle:
            return new rectangle(...);
    ...
    }
}
```

Be careful here we use shape* rather than shape which may leads to `object slicing`

How can we make sure not to leak memory when using the return value of create_shape?

The key is constructor and stack unwinding. We only need to store the return value into a local variable and make sure the destructor will delete this object.

```cpp
class shape_wrapper {
public:
    explicit shape_wrapper(
        shape* ptr = nullptr)
        : ptr_(ptr) {}
    ~shape_wrapper() {
        delete ptr_;
    }
    shape* get() const { return ptr_; }
private:
    shape* ptr_;
}

void foo() {
    ...
    shape_wrapper ptr_wapper(create_shape(...));
    ...
}

```

How about delete a nullptr? It's valid

The approximate process of new and delete:

```cpp
// new circle(...)
{
    // first alloc the memory. if fails, throw an exception(usually bac_alloc)
    void* temp = operator new(sizeof(circle));  
    try {
        circle* ptr = static_cast<circle*>(temp);
        ptr->circle(...);
        return ptr;
    }catch(...) {
        operator delete(ptr);
        throw;
    }
}
```

```cpp
if(ptr != nullptr) {
    ptr->~shape();
    operator delete(ptr);
}
```

In wrapper's destructor, we can do some clear work which is the basic use of RAII.

1. Free the memory

2. Close the file(fstream's destructor)

3. Release synchronization lock

4. Release system resources

For example:

We should write like this:

```cpp
std::mutex mtx;
void some_func() {
    std::lock_guard<std::mutex> guard(mtx);
    // do synchronized action
}
```

rather than:
```cpp
// Don't write like this
void some_func() {
    mtx.lock();
    // do synchronized action
    // if fail or return earlier
    // next statement will not be executed
    mtx.unlock();
}
```

By the way, we can see this shape_wrapper a simplest smart pointer

## In conclusion

We can use RAII which based on the stack and destructor to manage the system resources like heap efficiently.

## Questions

Compare to the smart pointer, what functions do shape_wrapper lack?



