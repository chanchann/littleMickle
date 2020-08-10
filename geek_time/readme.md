## 01 stack / heap / RAII : cpp resources management

## Basic concept 

### heap 

new / delete -> free store 

malloc / free -> heap

free store is the subspace of heap

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

1. Maybe it may throw an execption before delete action which Causes this operation to not be executed.

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

### RAII 

Resources Acquisition is Initializaiton


