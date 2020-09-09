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