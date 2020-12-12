/*
https://zhuanlan.zhihu.com/p/157833251

*/

#include <iostream>
#include <string>
using namespace std;

class People{
public:
    People(string name = "", int age = 0, float salary =0.0f);
    People(const People &peo);
    People& operator=(const People &peo);
    void Display();

private:
    string m_name;
    int m_age;
    float m_salary;
};

People::People(string name, int age, float salary):
m_name(name), m_age(age), m_salary(salary) { cout << "Constructor" << endl; }

People::People(const People &peo){
    this->m_name = peo.m_name;
    this->m_age = peo.m_age;
    this->m_salary = peo.m_salary;
    cout << "Copy constructor was called." << endl;
}

People& People::operator=(const People &peo){
    this->m_name = peo.m_name;
    this->m_age = peo.m_age;
    this->m_salary = peo.m_salary;
    cout << "operator=() was called." << endl;
    return *this;
}

void People::Display(){
    cout << m_name << ' ' << m_age << ' ' << m_salary << endl;
}

int main(int argc, char const *argv[]){
    People p1("Sam", 16, 10000);
    People p2("James", 17, 20000);
    
    People p4 = p1;   // Copy constructor was called. 因为第一次是初始化
    p4.Display();
    
    p4 = p2;       // operator=() was called. 后面就是赋值操作
    p4.Display();

    return 0;
}
