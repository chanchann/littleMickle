/*
1.         获取资源
2.         使用资源
3.         释放资源

void UseFile(char const* fn)
{
    FILE* f = fopen(fn, "r");        // 获取资源
    // 在此处使用文件句柄f...          // 使用资源
    fclose(f);                       // 释放资源
}
*/

// Not finished yet
#include <iostream>


class FileHandle {
public:
    FileHandle(char const* n, char const* a) { p = fopen(n, a); }
    ~FileHandle() { fclose(p); }
private:
    // 禁止拷贝操作
    // FileHandle对象代表一种资源，它并不具有拷贝语义，因此我们将拷贝构造函数和赋值运算符声明为私有成员
    FileHandle(FileHandle const&);
    FileHandle& operator= (FileHandle const&);
    FILE *p;
};

void UseFile(char const* fn)
{
    FileHandle file(fn, "r");
    return;
    // 在此处使用文件句柄f...
    // 超出此作用域时，系统会自动调用file的析构函数，从而释放资源
}

int main() {
    UseFile("./test.txt");
    return 0;
}

