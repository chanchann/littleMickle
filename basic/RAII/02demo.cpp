/*
File f;
f.open("boo.txt");
//UNSAFE - an exception here means the file is never closed
loadFromFile(f);
f.close();

Dog* dog = new Daschund;
//UNSAFE - an exception here means the dog is never deleted
goToThePark(dog); 
delete dog;

Lock* lock = getLock();
lock.aquire();
//UNSAFE - an exception here means the lock is never released
doSomething();
lock.release();

由于系统的资源不具有自动释放的功能，而C++中的类具有自动调用析构函数的功能。
如果把资源用类进行封装起来，对资源操作都封装在类的内部，在析构函数中进行释放资源。
当定义的局部变量的生命结束时，它的析构函数就会自动的被调用，
如此，就不用程序员显示的去调用释放资源的操作了。


*/

#include <iostream> 
using namespace std; 

class ArrayOperation { 
public : 
    ArrayOperation() { 
        m_Array = new int[10]; 
        cout << " Array created !! " << endl;
    } 

    void InitArray() { 
        for(int i = 0; i < 10; ++i) { 
            *(m_Array + i) = i; 
        } 
    } 

    void ShowArray() { 
        for(int i = 0; i < 10; ++i) { 
            cout << m_Array[i] << endl; 
        } 
    } 

    ~ArrayOperation() { 
        cout << " ~ArrayOperation is called " <<endl; 
        if (m_Array != NULL ) { 
            delete[] m_Array;  
            m_Array = NULL ; 
        } 
    } 

private : 
    int* m_Array; 
}; 

void Dosomething() {
    ArrayOperation arrayOp; 
    arrayOp.InitArray(); 
    arrayOp.ShowArray(); 
}

int main() 
{ 
    Dosomething();
    return 0;
}