#include <iostream>
using namespace std;
// https://blog.csdn.net/qq_29344757/article/details/76037255
// 如何利用gdb调试
// https://deepzz.com/post/gdb-debug.html
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
    cout << "11" << endl;
    p2 = p1;
    printf("%p\n", p1);
    printf("%p\n", p2);
    cout << *p2.m_age << endl;
}