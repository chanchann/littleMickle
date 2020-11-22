#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    cout << cin.tie()  << endl;  //打印cin的关联流的地址
    cout << &cout << endl;    //打印cout的地址
    cout << &cin << endl;      //打印地址
    cout << cout.tie() << endl;   //打印关联流地址

    cout << "tie the cerr to cout " << endl;
    cout.tie(&cerr);            //把cerr关联到cout
    cout << cout.tie() << endl;    //打印cout的关联流，即打印cerr的地址
    cout << &cerr << endl;          //打印cerr的地址
    cout.tie(nullptr);                    //彻底解开关联流，关联流都被解开了把？
    cout << "free the tie:" << cout.tie() << endl;  //

    cout.tie(nullptr);       //解开cout 的关联流
    cout << cout.tie() << endl;  
    cout << "tie the new:" << endl;
    ostream * old_tie  = cin.tie(nullptr);  //解开cin的挂链流,并且把cin原来的关联流返回
    cout << "old value: "<<  old_tie  << endl;        //
    cout << "now 's cin ' s tie is:" << cin.tie() << endl;

    return 0;
}