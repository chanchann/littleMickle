## const_cast

reference : https://www.geeksforgeeks.org/const_cast-in-c-type-casting-operators/

const_cast is used to cast away the constness of variables. 

1. const_cast can be used to change non-const class members inside a const member function.

2. const_cast can be used to pass const data to a function that doesn’t receive const

3. It is undefined behavior to modify a value which is initially declared as const. 