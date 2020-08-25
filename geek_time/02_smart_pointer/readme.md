## How to use smart pointer

## 21 days

Q1: Why slice ?

Q2: When slice ?

Q3 : Why deep copy solve slice ?
    
A smart pointer in C++ is a class, with overloaded operators, which behaves like a conventional pointer yet supplies additional value by ensuring proper and
timely destruction of dynamically allocated data and/or implementation of a well-defined object life-cycle management strategy.

```cpp
CData *pData = mObject.GetData();
/*
Questions: Is the object pointed to by pData dynamically allocated?
Who will perform the deallocation: caller or the called, if necessary?
Answer: No idea!
*/
pData->Display();
```

```cpp
// smart pointer 
smart_pointer<CData> spData = mObject.GetData();
// Use a smart pointer like a conventional pointer!
spData->Display();
(*spData).Display();
// Don’t have to worry about de-allocation
// (the smart pointer’s destructor does it for you)
```

**How did the smart pointer spData function like a conventional pointer?**

Smart pointer classes overload
operator* (dereferencing operator) and operator-> (member selection operator) to
make you, the programmer, use them as conventional pointers. 

A simple inplementation:

```cpp
template <typename T>
class smart_pointer {
private:
    T* m_pRawPointer;
public:
    // constructor
    smart_pointer(T* pData) : m_pRawPointer(pData) {} 
    // destructor
    ~smart_pointer() {delete pData;}; 
    // copy constructor
    smart_pointer(const smart_pointer & anotherSP);
    // assignment operator
    smart_pointer& operator=(const smart_pointer& anotherSP); 
    // dereferencing operator
    T& operator*() const {
        return *(m_pRawPointer);
    }
    // member selection operator
    T* operator->() const {
        return m_pRawPointer;
    }
};
```

## Types of SP

Classification of smart pointers is actually a classification of their memory resource management strategies

- Deep Copy

- Copy on Write (COW)

- Reference counted

- Reference linked

- Destructive copy

## Deep Copy

Every smart pointer instance holds a complete copy of the object that is being managed. Whenever the smart pointer is copied, the
object pointed to is also copied (thus, deep copy). When the smart pointer goes out of
scope, it releases the memory it points to (via the destructor).

Its advantage becomes apparent in the treatment of polymorphic objects, where it can avoid slicing.

```cpp
// Example of Slicing When Passing Polymorphic Objects by Value
// CAnimal is a base class for CDog and CCat.
void MakeAnimalTalk (CAnimal mAnimal) {
    mAnimal.Talk(); // virtual function
}
// ... Some function
CCat mCat;
MakeAnimalTalk(mCat);
// Slicing: only the CAnimal part of mCat is sent to MakeAnimalTalk
CDog mDog;
MakeAnimalTalk(mDog); // Slicing again
```

Slicing issues are resolved when the programmer chooses a deep-copy smart pointer

```cpp

template <typename T>
class deepcopy_smart_pointer {
private:
    T* m_pObject;
public:
    //... other functions

    // copy constructor of the deepcopy pointer
    deepcopy_smart_pointer(const deepcopy_smart_pointer& source){
    // Use a virtual clone function defined in the derived class
    // to get a complete copy of the object
        m_pObject = source->Clone();
    }
    
    // copy assignment operator
    deepcopy_smart_pointer& operator=(const deepcopy_smart_pointer& source){
        if(m_pObject) {
            delete m_pObject;
        }
        m_pObject = source->clone();
    }
};

void MakeAnimalTalk(deepcopy_smart_pointer<CAnimal> mAnimal) {
    mAnimal.Talk ();
}

// use 
deepcopy_smart_pointer <CAnimal> pDog(new CDog());
MakeAnimalTalk(pDog); // No slicing issues as pDog is deep-copied
```

## cpp primer

## static memory / stack / heap

**Static memory** is used for local static objects, for class static data members and for variables defined outside any function. Static objects are allocated before they are used, and they are destroyed when the program ends.

**Stack memory** is used for **non static** objects defined inside functions. Stack objects exist only while the block in which they are defined is executing; 

**Heap** for objects that they dynamically allocate—that is, for objects that the
program allocates at run time. The program controls the lifetime of dynamic objects; our code must explicitly destroy such objects when they are no longer needed

## shared_ptr 

```cpp
shared_ptr<string> p1; // shared_ptr that can point at a string
shared_ptr<list<int> > p2; // shared_ptr that can point at a list of ints
```

### make_shared 

The safest way to allocate and use dynamic memory.

```cpp
// shared_ptr that points to an int with value 42
shared_ptr<int> p3 = make_shared<int>(42);
// p4 points to a string with value 9999999999
shared_ptr<string> p4 = make_shared<string>(10, '9');
// p5 points to an int that is value initialized to 0
shared_ptr<int> p5 = make_shared<int>();

//ordinarily we use auto
// p6 points to a dynamically allocated, empty vector<string>
auto p6 = make_shared<vector<string>>();
```

### Copying and Assigning shared_ptrs

When we copy or assign a shared_ptr, each shared_ptr keeps track of how many
other shared_ptrs point to the same object:

```cpp
auto p = make_shared<int>(42); // object to which p points has one user
auto q(p); // p and q point to the same object
// object to which p and q point has two users
```

**reference count**: 

copy a shared_ptr, the count is incremented

- initialize another shared_pt

- right-hand operand of an assignment

- pass it to or return it from a function by value

The counter is decremented when we assign a new value to the shared_ptr and when the shared_ptr itself is destroyed, such as when a local shared_ptr goes out of scope

```cpp
auto r = make_shared<int>(42); // int to which r points has one user
r = q; // assign to r, making it point to a different address
// increase the use count for the object to which q points
// reduce the use count of the object to which r had pointed
// the object r had pointed to has no users; that object is automatically freed
```

### shared_ptrs Automatically Destroy Their Objects ...

If the count goes to zero, the shared_ptr destructor destroys the object to which the shared_ptr points and frees the memory used by that object.

### ...and Automatically Free the Associated Memory

```cpp
// factory returns a shared_ptr pointing to a dynamically allocated object
shared_ptr<Foo> factory(T arg) {
// process arg as appropriate
// shared_ptr will take care of deleting this memory
return make_shared<Foo>(arg);
}
```

```cpp
void use_factory(T arg) {
shared_ptr<Foo> p = factory(arg);
// use p
} // p goes out of scope; the memory to which p points is automatically freed
```

In this case, p is the only object referring to the memory returned by factory. Because p is about to go away, the object to which p points will be destroyed and the memory in which that object resides will be freed.

```cpp
// The memory will not be freed if there is any other shared_ptr pointing to it:
shared_ptr<Foo> use_factory(T arg) {
shared_ptr<Foo> p = factory(arg);
// use p
return p; // reference count is incremented when we return p
} // p goes out of scope; the memory to which p points is not freed
```
Because memory is not freed until the last shared_ptr goes away, it can be important to be sure that shared_ptrs don’t stay around after they are no longer needed.

**If you put shared_ptrs in a container, and you subsequently need to use some, but not all, of the elements, remember to erase the elements you no longer need.**

### Classes with Resources That Have Dynamic Lifetime

Programs tend to use dynamic memory for one of three purposes:

1. They don’t know how many objects they’ll need (for instance : container)
2. They don’t know the precise type of the objects they need
3. They want to share data between several objects


### Defining the StrBlob Class

we’ll define a class that uses dynamic memory in order to let several objects share the same underlying data.

```cpp
vector<string> v1; // empty vector
{ // new scope
vector<string> v2 = {"a", "an", "the"};
v1 = v2; // copies the elements from v2 into v1
} // v2 is destroyed, which destroys the elements in v2
// v1 has three elements, which are copies of the ones originally in v2
```

The elements allocated by a vector exist only while the vector itself exists. When a vector is destroyed, the elements in the vector are also destroyed.

Some classes allocate resources with a lifetime that is independent of the original object.

```cpp
Blob<string> b1; // empty Blob 
{   // new scope
    Blob<string> b2 = {"a", "an", "the"};
    b1 = b2; // b1 and b2 share the same elements
} 
// b2 is destroyed, but the elements in b2 must not be destroyed
// b1 points to the elements originally created in b2
```

We can’t store the vector directly in a Blob object. Members of an object are destroyed when the object itself is destroyed. For example, assume that b1 and b2 are two Blobs that share the same vector. If that vector were stored in
one of those Blobs—say, b2—then that vector, and therefore its elements, would no longer exist once b2 goes out of scope. To ensure that the elements continue to exist, we’ll store the vector in dynamic memory.

See [strBlob](./strBlob)

