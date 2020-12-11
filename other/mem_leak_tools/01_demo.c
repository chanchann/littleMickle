/*
gcc -g -o test 01_demo.c 

valgrind --tool=memcheck --leak-check=full ./test

valgrind:  Fatal error at startup: a function redirection

sudo apt-get install libc6-dbg

申请未释放

==19146== LEAK SUMMARY:
==19146==    definitely lost: 4 bytes in 1 blocks
==19146==    indirectly lost: 0 bytes in 0 blocks
==19146==      possibly lost: 0 bytes in 0 blocks
==19146==    still reachable: 0 bytes in 0 blocks
==19146==         suppressed: 0 bytes in 0 blocks

*/

#include <stdlib.h>

int main() {
    int *array = malloc(sizeof(int));
    return 0;
}
