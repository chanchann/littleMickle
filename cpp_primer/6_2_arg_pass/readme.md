## 6.2 Argument Passing

- Passing Arguments by Value

- Pointer Parameters

- Passing Arguments by Reference

Using References to Avoid Copies

Reference parameters that are not changed inside a function should be references to const.

```
string::size_type guarantees just that. It is a type that is big enough to represent the size of a string, no matter how big that string is

The string class and most other library types defines several companion types.
These companion types make it possible to use the library types in a machine independent manner.

It is an unsigned type big enough to hold the size of any string. Any variable used to store the result from the string size operation should be of type string::size_type.

Under the new standard, we can ask the compiler to provide the appropriate type by using auto or decltype.

auto len = line.size(); // len has type string::size_type
```

```
tips:

It is essential to remember that expressions that mix signed and unsigned data can have surprising results.

You can avoid problems due to conversion between unsigned and int by not using ints in expressions that use size().
```



