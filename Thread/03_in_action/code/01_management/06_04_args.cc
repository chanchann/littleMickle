/*
函数f需要一个std::string对象作为第二个参数，但这里使用的是字符串的字面值，也就是char const *类型。
之后，在线程的上下文中完成字面值向std::string对象的转化。需要特别要注意，当指向动态变量的指针作为参数传递给线程的情况
void f(int i,std::string const& s);
void oops(int some_param) {
  char buffer[1024]; // 1
  sprintf(buffer, "%i",some_param);
  std::thread t(f,3,buffer); // 2
  t.detach();
}

buffer②是一个指针变量，指向本地变量，然后本地变量通过buffer传递到新线程中②。
并且，函数有很有可能会在字面值转化成std::string对象之前崩溃(oops)，从而导致一些未定义的行为。
并且想要依赖隐式转换将字面值转换为函数期待的std::string对象，
但因std::thread的构造函数会复制提供的变量，就只复制了没有转换成期望类型的字符串字面值。

*/

#include <iostream>
#include <string>
#include <thread>

void f(int i,std::string const& s) {
    std::cout << i << s << std::endl;
};

void not_oops(int some_param) {
    char buffer[1024];
    sprintf(buffer,"%i",some_param);
    std::thread t(f, 3, std::string(buffer));  // 使用std::string，避免悬垂指针
    t.detach();
}
int main() {
    not_oops(100);
    return 0;
}