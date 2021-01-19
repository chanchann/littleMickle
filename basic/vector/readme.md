## C++ : How to find an element in vector and get its index ?

https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/

## reserver and resize

 vector 的reserve增加了vector的capacity，但是它的size没有改变！而 resize 改变了vector的capacity 同时也增加了它的size！

 https://blog.csdn.net/u014082714/article/details/44221369

 ## std::vector::emplace_back and std::move

```cpp
std::string str("some_string");
bar.emplace_back(std::move(str));
```

https://stackoverflow.com/questions/26860749/efficiency-of-c11-push-back-with-stdmove-versus-emplace-back-for-already/26861516

https://stackoverflow.com/questions/35404932/stdvectoremplace-back-and-stdmove