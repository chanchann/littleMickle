//testGdb.c
#include<stdio.h>
#include<stdlib.h>
#include"testGdb.h"
int main(void) {
    int a = 10; //整型
    int b[] = {1,2,3,5};  //数组
    char c[] = "hello,shouwang";//字符数组
    /*申请内存，失败时退出*/    
    int *d = (int*)malloc(a*sizeof(int));
    if(NULL == d)
    {
        printf("malloc error\n");
        return -1;
    }
    /*赋值*/
    for(int i=0; i < 10;i++)
    {
        d[i] = i;
    }
    free(d);
    d = NULL;
    float e = 8.5f;
    return 0;
}