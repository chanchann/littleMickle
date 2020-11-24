#include <iostream>
using namespace std;

int main() {
    int i1[3] = {1, 2, 3};
    int* p1;
    // p2是一个数组，数组有3个元素，每个元素都是int*
    int* p2[3];
    //p3是一个指针，指向一个数组，数组中有3个元素
    int(*p3)[3];
    //p4是一个二重指针
    int **p4;

    // p1 = &i1;//错误，类型不匹配
    // p2 = &i1;//错误，不能把指针赋给数组
    p3 = &i1;
    // p4 = &i1;//错误，类型不匹配

    return 0;
}