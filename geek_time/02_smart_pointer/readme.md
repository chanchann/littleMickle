## How to use smart pointer

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


