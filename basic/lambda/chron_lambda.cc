// g++ lambda.cpp -std=c++14 -o a.out;./a.out
// g++ lambda.cpp -std=c++14 -I../common -o a.out;./a.out
/*
TODO : 什么是闭包
TODO: 用“map+lambda”的方式来替换难以维护的 if/else/switch
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void my_square(int x) {
    cout << x * x << endl;
}

void case1() {
    auto pfunc = &my_square;   // 只能用指针去操作函数，指针不是函数

    (*pfunc)(3);   // 可以用*访问函数 
    pfunc(3);     // 也可以直接调用函数指针

    auto func = [](int x) {
        cout << x*x << endl;
    };

    func(3);
}

// 捕获外部变量
void case2() {
    int n = 10; 

    auto func = [=](int x) { // = 值捕获
        cout << x*n << endl;  // 直接操作外部变量
    };

    func(3);
}

// lambda的形式
void case3() {
    auto f1 = [](){};

    auto f2 = []() {
        cout << "lambda f2" << endl;

        auto f3 = [](int x) {  // 嵌套定义lambda表达式
            return x*x;
        };// lambda f3  使用注释显式说明表达式结束

        cout << f3(10) << endl;
    };  // lambda f2

    f1();
    f2();

    //f1 = f2;

    vector<int> v = {3, 1, 8, 5, 0};

    cout << *find_if(begin(v), end(v),    // 标准库里的查找算法
                [](int x) {             // 匿名lambda表达式，不需要auto赋值
                    return x >= 5;
                }
            )
         << endl;
}

// lambda的变量捕获
// “[=]”表示按值捕获所有外部变量，表达式内部是值的拷贝，并且不能修改；
// “[&]”是按引用捕获所有外部变量，内部以引用的方式使用，可以修改；
// 你也可以在“[]”里明确写出外部变量名，指定按值或者按引用捕获，C++ 在这里给予了非常大的灵活性。
void case4() {
    int x = 33;

    auto f1 = [=]() {
        //x += 10;    // x只读，不允许修改
        cout << x << endl;
    };

    auto f2 = [&]() {
        x += 10;  // x是引用，可以修改
    };

    auto f3 = [=, &x]() {  // lambda表达式，用“&”按引用捕获x，其他的按值捕获
        x += 20;
    };

    f1();
    f2();
    cout << x << endl;
    f3();
    cout << x << endl;
}

class DemoLambda final {
public:
    DemoLambda() = default;
   ~DemoLambda() = default;
private:
    int x = 0;
public:
    auto print() {      // 返回一个lambda表达式供外部使用
        //auto f = [=]()

        return [this]() {       // 显式捕获this指针
            cout << "member = " << x << endl;
        };

    }
};

void case5() {
    DemoLambda obj;

    auto f = obj.print();

    f();
}

void case6() {
    auto f = [](const auto& x) {  // 参数使用auto声明，泛型化
        return x + x;
    };

    cout << f(3) << endl;
    cout << f(0.618) << endl;

    string str = "matrix";
    cout << f(str) << endl;
}

// demo for function + lambda
class Demo final {
public:
    using func_type = std::function<void()>;
public:
    func_type print = [this]() {
        cout << "value = " << m_value << endl;
        cout << "hello function+lambda" << endl;
    };
private:
    int m_value = 10;
};

int main() {
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();

    Demo d;
    d.print();

    cout << "lambda demo" << endl;
}