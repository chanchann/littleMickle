## C++11中range-based for loops中&&与&的区别

https://blog.csdn.net/haolexiao/article/details/56842552

https://stackoverflow.com/questions/15927033/what-is-the-correct-way-of-using-c11s-range-based-for

##  in generic code, the following guidelines can be provided:

- For observing the elements, use:

for (const auto& elem : container)

- For modifying the elements in place, use:

for (auto&& elem : container)