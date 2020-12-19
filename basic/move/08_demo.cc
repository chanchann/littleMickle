#include <deque>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

//std::move进行右值引用，可以将左值和右值转为右值引用， 这种操作意味着被引用的值将不再被使用，否则会引起“不可预期的结果”。
class Base {
public:
    Base(int k) {
        p = new int(1);
        q = *p = k;
    }

    ~Base() {
        delete p;
    }
    void show() {
        cout << "q address: " << &q <<endl;
        cout << "p address: " << p <<endl;
    }
private:
    int q;
    int *p;
};

// 这里就可以看出move没有转移置空功能
void test01() {
    cout << endl << "常规变量-----------------------------------------" << endl;
    int k = 6, s = 7;
    cout << k << " " << s << endl;  
    k = std::move(s);
    cout << k << " " << s << endl;
    k = 8;
    cout << k << endl;
}

void test02() {
    cout << endl << "vector(自动清空）-----------------------------------------" << endl;
    vector<int> data1 = {1, 2};
    vector<int> data2 = {1, 3, 4, 5, 4, 3, 5, 2};
    data1 = std::move(data2);
//     data1 = static_cast<vector<int> &&>(data2);
    cout<< "after move:" << endl<< "data1:";
    for (int foo : data1)  cout << foo << " ";

    cout << endl<< "data2:";
    for (int foo : data2)  cout << foo << " ";
}

void test03() {
    cout<< endl << "指针变量-----------------------------------------" << endl;
    int m = 3, n = 5;
    int *p = &m, *q = &n;
    cout << "Before move : " << endl;
    cout << p << "       " << *p << endl;
    cout << q << "       " << *q << endl;
    p = std::move(q);
    cout << "After move : " << endl;    
    cout << p << "       " << *p << endl;
    cout << q << "       " << *q << endl;
}

// 导致double free or corruption
// 未定义move constuctor
void test04() {
    cout << endl << "class 对象-----------------------------------------" << endl;
    Base ba(5);
    Base bb(2);
    cout << "Before move : " << endl;
    ba.show();
    bb.show();
    bb = std::move(ba);
    cout << "After move : " << endl;
    ba.show();
    bb.show();
}

// 很奇特的答案
void test05() {
    cout << endl << "string（不是自动清空） -----------------------------------------" << endl;
    string str = std::move("111");
    string str1("222");
    cout << "Before move : " << endl;
    cout << "str : " << &str << "   " << str << endl;
    cout << "str1 : " << &str1 << "   " << str1 << endl;
    str1 = std::move(str);
    cout << "After move : " << endl;
    cout << "str : " << &str << "   " << str << endl;
    cout << "str1 : " << &str1 << "   " << str1 << endl;
}

void test06() {
    std::string str = "Hello";
    std::vector<std::string> v;
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";
    std::cout << "The contents of the vector are \"" << v[0]
                                         << "\", \"" << v[1] << "\"\n";
}


int main() {
    test01();
    test02();
    test03();
    // test04(); error
    test05();
    test06();

    return 0;
}