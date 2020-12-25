/*
https://www.cnblogs.com/DswCnblog/p/5629165.html

*/

#include <iostream>
using namespace std;

// 捕获外部变量
void test01() {
    cout << "----------- test01 ------------" << endl;
    int a = 123;
    auto f = [a] { 
        cout << a << endl;  
        // a++;    // read-only
    }; 
    f(); // 输出：123

    //或通过“函数体”后面的‘()’传入参数
    [](int a){cout << a << endl;}(333); 
}
/*
值捕获
被捕获的变量的值在Lambda表达式创建时通过值拷贝的方式传入，
因此随后对该变量的修改不会影响影响Lambda表达式中的值

如果以传值方式捕获外部变量，则在Lambda表达式函数体中不能修改该外部变量的值
*/
void test02() {
    cout << "----------- test02 ------------" << endl;
    int a = 123;
    auto f = [a] { cout << a << endl; }; 
    a = 321;
    f(); // 输出：123
}

// 引用捕获
void test03() {
    cout << "----------- test03 ------------" << endl;
    int a = 123;
    auto f = [&a] { cout << a << endl; }; 
    a = 321;
    f(); // 输出：321
}

/*
隐式捕获
[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量。
让编译器根据函数体中的代码来推断需要捕获哪些变量
*/

void test04() {
    cout << "----------- test04 ------------" << endl;
    int a = 123;
    auto f = [=] { cout << a << endl; };    // 值捕获
    f(); // 输出：123    
}

void test05() {
    cout << "----------- test05 ------------" << endl;
    int a = 123;
    auto f = [&] { cout << a << endl; };    // 引用捕获
    a = 321;
    f(); // 输出：321    
}

// TODO: 混合方式

/*
修改捕获变量

有没有办法可以修改值捕获的外部变量呢？
这是就需要使用mutable关键字，该关键字用以说明表达式体内的代码可以修改值捕获的变量
*/

void test06() {
    cout << "----------- test06 ------------" << endl; 
    int a = 123;
    auto f = [a]()mutable { cout << ++a; }; // 不会报错
    cout << a << endl; // 输出：123
    f(); // 输出：124
}
int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
}