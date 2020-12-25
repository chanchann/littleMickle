/*
调试启动带参程序

$ gdb test
(gdb)run 'para'

------------------

$ gdb test
(gdb) set args 'para'
(gdb) run
*/

#include<stdio.h>
int main(int argc,char *argv[]) {
    if(1 >= argc) {
        printf("usage:hello name\n");
        return 0;
    }
    printf("Hello World %s!\n",argv[1]);
    return 0 ;
}
