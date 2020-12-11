/*
使用未初始化的内存

==19334== Conditional jump or move depends on uninitialised value(s)
==19334==    at 0x4005F3: main (in /home/ysy/thread/other/mem_leak_tools/test)
*/

#include <cstdio>

int main() {
    // a[2]未初始化
    int a[5];
    int i, s;
    a[0] = a[1] = a[3] = a[4] = 0;
    s = 0;
    for(i = 0; i < 5; i++)
        s += a[i];
    if(s == 377)
        printf("sum is %d\n", s);
    return 0;
}