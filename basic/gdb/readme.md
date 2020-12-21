## 如何利用gdb调试

https://deepzz.com/post/gdb-debug.html

https://blog.csdn.net/haoel/article/details/2879


## cgdb

https://www.bookstack.cn/read/cgdb-manual-in-chinese/4.0.md

https://cgdb.github.io/

https://williamlfang.github.io/post/2020-05-31-cgdb-%E5%AE%89%E8%A3%85%E4%B8%8E%E4%BD%BF%E7%94%A8/

TODO : 解决中文

## 常用

g++ -g test.cc -o test 

gdb test -tui

disas /m

r 运行

n 单步执行(不进入函数)

s 单步执行(进入函数)

c 执行到断点

u 执行到指定行(until)

finish 从进入的函数中退出

break 设置断点(在代码窗口用空格键设置断点)