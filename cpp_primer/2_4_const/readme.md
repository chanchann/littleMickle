# 2.4 const Qualifier

Because we can’t change the value of a const object after we create it, it must be initialized.

```cpp
const int i = get_size(); // ok: initialized at run time
const int j = 42; // ok: initialized at compile time
const int k; // error: k is uninitialized const
```

when we use an object to initialize another object, it doesn’t matter  whether either or both of the objects are consts:

```cpp
int i = 42;
const int ci = i; // ok: the value in i is copied into ci
int j = ci; // ok: the value in ci is copied into j
```

### By Default, const Objects Are Local to a File

To substitute the value for the variable, the compiler has to see the variable’s initializer. When we split a program into multiple files, every file that uses the const must have access to its initializer. In order to see the initializer, the variable must be defined in every file that wants to use the variable’s value (§ 2.2.2). To support this usage, yet avoid multiple definitions of the same variable, const variables are defined as local to the file. When we define a const with the same name in multiple files, it is as if we had written definitions for separate variables in each file.

BUT ! 

How to define the const in one file, and declare it in the other files that use that object?

To define a single instance of a const variable, we use the keyword extern on both its definition and declaration(s):

```cpp
// file_1.cc defines and initializes a const that is accessible to other files
extern const int bufSize = fcn();
// file_1.h
extern const int bufSize; // same bufSize as defined in file_1.cc
```

## 2.4.1. References to const

```cpp
const int ci = 1024;
const int &r1 = ci; // ok: both reference and underlying object are const
r1 = 42; // error: r1 is a reference to const
int &r2 = ci; // error: non const reference to a const object
```

## Initialization and References to const

We noted that there are two exceptions to the rule that the type of a reference must match the type of the object to which it refers

The first exception is that we can initialize a reference to const from any expression that can be converted to the type of the reference

```cpp
// In particular, we can bind a reference to
const to a nonconst object, a literal, or a more general expression:

int i = 42;
const int &r1 = i; // we can bind a const int& to a plain int object
const int &r2 = 42; // ok: r2 is a reference to const
const int &r3 = r1 * 2; // ok: r3 is a reference to const
int &r4 = r * 2; // error: r4 is a plain, non const reference
```

```cpp
double dval = 3.14;
const int &ri = dval;
// Here ri refers to an int.  Operations on ri will be integer operations, but dval is a floating-point number, not an integer. To ensure that the object to which ri is bound is an int, the compiler transforms this code into something like

const int temp = dval; // create a temporary const int from the double
const int &ri = temp; // bind ri to that temporary
// In this case, ri is bound to a temporary object. A temporary object is an unnamed object created by the compiler when it needs a place to store a result from evaluating an expression.
//  If ri weren’t const, we could assign to ri. Doing so would change the object to which ri is bound. That object is a temporary, not dval.
```

## A Reference to const May Refer to an Object That Is Not const

```cpp
int i = 42;
int &r1 = i; // r1 bound to i
const int &r2 = i; // r2 also bound to i; but cannot be used to change i
r1 = 0; // r1 is not const; i is now 0
r2 = 0; // error: r2 is a reference to const
```

It is important to realize that a reference to const restricts only what we can do
through that reference. Binding a reference to const to an object says nothing about
whether the underlying object itself is const. Because the underlying object might be
nonconst, it might be changed by other means:

## 2.4.2. Pointers and const

A pointer to const may not be used to change the object to which the pointer points. We may store the address of a const object only in a pointer to const

```cpp
const double pi = 3.14; // pi is const; its value may not be changed
double *ptr = &pi; // error: ptr is a plain pointer
const double *cptr = &pi; // ok: cptr may point to a double that is const
*cptr = 42; // error: cannot assign to *cptr
```

There are two exceptions to the rule that the types of a pointer and the object to which it points must match. The first exception is that we can use a pointer to const to point to a nonconst object:

```cpp
double dval = 3.14; // dval is a double; its value can be changed
cptr = &dval; // ok: but can't change dval through cptr
```

Defining a pointer as a pointer to const affects only what we can do  with the pointer. It is important to remember that there is no guarantee that an object pointed to by a pointer to const won’t change.

## In conclusion

1. The first exception is that we can use a pointer to const to point to a nonconst object:

2. only const int& a = b(double); can convert 

see [exception1](./exception1.cpp)

## const Pointers

Unlike references, pointers are objects. 

we can have a pointer that is itself const.

Like any other const object, a const pointer
must be initialized, and once initialized, its value (i.e., the address that it holds) may
not be changed

We indicate that the pointer is const by putting the const after the
*. This placement indicates that it is the pointer, not the pointed-to type, that is
const:

```cpp
int errNumb = 0;
int *const curErr = &errNumb; // curErr will always point to errNumb
const double pi = 3.14159;
const double *const pip = &pi; // pip is a const pointer to a const
object
```
