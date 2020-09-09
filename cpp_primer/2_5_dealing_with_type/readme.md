# 2.5 Dealing with Types

## 2.5.1. Type Aliases

### typeof

```cpp
typedef double wages; // wages is a synonym for double
typedef wages base, *p; // base is a synonym for double, p for double*
```

### alias declaration : using

using SI = Sales_item; // SI is a synonym for Sales_item


### Pointers, const, and Type Aliases

Be careful :

```cpp
typedef char *pstring;
const pstring cstr = 0; // cstr is a constant pointer to char
const pstring *ps; // ps is a pointer to a constant pointer to char
//The type of pstring is “pointer to char.” So, const pstring is a constant pointer to char not a pointer to const char
```

It can be tempting, albeit incorrect, to interpret a declaration that uses a type alias by conceptually replacing the alias with its corresponding type.

```cpp
const char *cstr = 0; // wrong interpretation of const pstring cstr
//this interpretation is wrong. When we use pstring in a declaration, the base type of the declaration is a pointer type. When we rewrite the declaration using char*, the base type is char and the * is part of the declarator. In this case, const char is the base type. This rewrite declares cstr as a pointer to const char rather than as a const pointer to char.
```

## 2.5.2. The auto Type Specifier

A variable that uses **auto** as its type specifier must have an initializer

```cpp
// the type of item is deduced from the type of the result of adding val1 and val2
auto item = val1 + val2; // item initialized to the result of val1 + val2
```
### we can define multiple variables using auto.

Because a declaration can involve only a single base type, the initializers for all the variables in the declaration must have types that are consistent with each other:

```cpp
auto i = 0, *p = &i; // ok: i is int and p is a pointer to int
auto sz = 0, pi = 3.14; // error: inconsistent types for sz and pi
```

## Compound Types, const, and auto

The type that the compiler infers for auto is not always exactly the same as the initializer’s type. Instead, the compiler adjusts the type to conform to normal initialization rules.

### Use a reference as an initializer, the initializer is the corresponding object.

```cpp
int i = 0, &r = i;
auto a = r; // a is an int (r is an alias for i, which has type int)
```

### auto ordinarily ignores top-level consts(&2.4.3). As usual in initializations, low-level consts, such as when an initializer is a pointer to const, are kept:
