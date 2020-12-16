/*
=号的运算符重载
*/

#include <iostream>
using namespace std;

class Student {
public:
    int m_age;

    // 无参构造函数
    Student() {
        m_age = 10;
        cout << "无参构造函数" << endl;
    }

    // 复制构造函数
    Student(const Student& s) {
        m_age = s.m_age;
        cout << "复制构造函数" << endl;
    }

    // 等号运算符重载
    Student &operator=(const Student& s) {
        cout << "等号运算符重载" << endl;
        // 如果是对象本身, 则直接返回
        if (this == &s) {
            return *this;
        }

        // 复制等号右边对象的成员值到等号左边对象的成员
        this->m_age = s.m_age;
        return *this;
    }
};

int main() {
    Student stu1;       // 调用无参构造函数
    Student stu2(stu1); // 调用复制构造函数
    printf("stu1: %d, stu2: %d\n", stu1.m_age, stu2.m_age);

    stu2.m_age = 22;
    stu1 = stu2;        // 等号运算符重载
    printf("stu1: %d, stu2: %d\n", stu1.m_age, stu2.m_age);

    return 0;
}