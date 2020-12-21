/*
这个例子去学会使用gdb

查看汇编了解inline的真实作用
https://zhuanlan.zhihu.com/p/50812510

结合使用vscode解决问题

这个是浅拷贝带来的问题
https://blog.csdn.net/qq_29344757/article/details/76037255

*/


#include <iostream>
using namespace std;

class Person {
public:
	explicit Person(int age) : m_age(new int(age)) {}

	// Person& operator=(const Person& p)
	// {
	// 	cout << "Assign" << endl;
	// 	return *this;
	// }

	Person* operator=(const Person* p) {
        cout << "copy assignment" << endl;
        if(m_age != NULL) {
            delete m_age;
            m_age = NULL;
        }
        m_age = new int(*(p->m_age));
        return this;
	}
    ~Person() {
        if(m_age != NULL) {
            delete m_age;
            m_age = NULL;
        }
        cout << "free" << endl;
    }

	int* m_age;
};

int main() {
    Person p1(10);
    Person p2(15);
    std::string test = "中文";
    cout << "11" << endl;
    // p2 = &p1;
    p2 = p1;
    printf("%p\n", p1);
    printf("%p\n", p2);
    cout << *p2.m_age << endl;
}