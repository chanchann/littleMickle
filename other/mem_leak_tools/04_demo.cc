/*
内存读写越界

==19430== Invalid write of size 4
==19430==    at 0x4005B0: main (in /home/ysy/thread/other/mem_leak_tools/test)
==19430==  Address 0x5204050 is 0 bytes after a block of size 16 alloc'd
==19430==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==19430==    by 0x400585: main (in /home/ysy/thread/other/mem_leak_tools/test)
==19430== 
==19430== Invalid read of size 4
==19430==    at 0x4005BA: main (in /home/ysy/thread/other/mem_leak_tools/test)
==19430==  Address 0x5204050 is 0 bytes after a block of size 16 alloc'd
==19430==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==19430==    by 0x400585: main (in /home/ysy/thread/other/mem_leak_tools/test)
==19430== 
*/

#include <cstdio>
#include <cstdlib>

int main() {
    int len = 4;
    int *pt = (int *)malloc(len * sizeof(int));
    int *p = pt;
    for(int i = 0; i < len; i++)
        p++;
    *p = 4;  // 越界
    printf("the value of p equal:%d", *p);
    return 0;
}