/*
https://blog.csdn.net/weibo1230123/article/details/81530355
*/

#include <stdio.h>
#include <sys/uio.h>
#include <string.h>
int main() {
    static char part1[] = "[";
    static char part2[] = "Hello world";
    static int part3 = 65;
    
    struct iovec iov[3];

    iov[0].iov_base = part1;
    iov[0].iov_len = strlen(part1);

    iov[1].iov_base = part2;
    iov[1].iov_len = strlen(part2);

    iov[2].iov_base = &part3;
    iov[2].iov_len = sizeof(int);

    writev(1, iov, 3);

}