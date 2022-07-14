## placement new

Placement new allows you to construct an object in memory that's already allocated.

```cpp
char *buf  = new char[sizeof(string)]; // pre-allocated buffer
string *p = new (buf) string("hi");    // placement new
string *q = new string("hi");          // ordinary heap allocation
```

## Is there a "placement delete"?



## ref

https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new

https://www.stroustrup.com/bs_faq2.html#placement-delete