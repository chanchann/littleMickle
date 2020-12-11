
/*
==19754== HEAP SUMMARY:
==19754==     in use at exit: 72,704 bytes in 1 blocks
==19754==   total heap usage: 2 allocs, 1 frees, 72,736 bytes allocated

这个程序并没有发生内存泄漏，但是从HEAP SUMMARY可以看到，程序分配了 2 次内存，但却只释放了 1 次内存，为什么会这样呢？

实际上这是由于 C++ 在分配内存时，为了提高效率，使用了它自己的内存池。当程序终止时，内存池的内存才会被操作系统回收，所以 Valgrind 会将这部分内存报告为 reachable 的，需要注意，reachable 的内存不代表内存泄漏
*/
#include <string>
int main() {
    auto ptr = new std::string("Hello, World!");
    delete ptr;
    return 0;
}