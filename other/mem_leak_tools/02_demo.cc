/*
申请的堆内存没有释放 + 对堆内存的访问越界

==19218== Invalid write of size 4
==19218==    at 0x400547: fun() (in /home/ysy/thread/other/mem_leak_tools/test)
==19218==    by 0x400558: main (in /home/ysy/thread/other/mem_leak_tools/test)
==19218==  Address 0x5204068 is 0 bytes after a block of size 40 alloc'd
==19218==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==19218==    by 0x40053A: fun() (in /home/ysy/thread/other/mem_leak_tools/test)
==19218==    by 0x400558: main (in /home/ysy/thread/other/mem_leak_tools/test)


==19218== LEAK SUMMARY:
==19218==    definitely lost: 40 bytes in 1 blocks
==19218==    indirectly lost: 0 bytes in 0 blocks
==19218==      possibly lost: 0 bytes in 0 blocks
==19218==    still reachable: 0 bytes in 0 blocks
==19218==         suppressed: 0 bytes in 0 blocks
==19218== 
*/

#include <cstdlib>

void fun() {
    int *p = (int *)malloc(10 * sizeof(int));
    p[10] = 0;
}

int main() {
    fun();
    return 0;
}