/* 
内存覆盖
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    char x[50];
    int i;
    for(i = 0; i < 50; i++)
        x[i] = i + 1;
    strncpy(x + 20, x, 20); //ok
    strncpy(x + 20, x, 21); //overlap
    strncpy(x, x + 20, 20); //ok
    strncpy(x, x + 20, 22); //overlap
    x[39] = '\0';
    strcpy(x, x + 20);      //ok
    x[39] = 39;
    x[40] = '\0';
    strcpy(x, x + 20);      //overlap
    return 0;
}