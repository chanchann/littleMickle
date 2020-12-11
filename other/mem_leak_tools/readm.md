## 使用 Valgrind 检测 C++ 内存泄漏

https://www.cnblogs.com/shuaihanhungry/p/5818713.html

http://senlinzhan.github.io/2017/12/31/valgrind/

gcc -g -o test 01_demo.c 

valgrind --tool=memcheck --leak-check=full ./test
