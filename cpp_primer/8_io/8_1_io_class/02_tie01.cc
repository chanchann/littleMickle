/*
将tiestr指向的输出流绑定的该对象上，并返回上一个绑定的输出流指针
ostream* tie ( ostream* tiestr ); 

如果该对象没有绑定输出流,则返回空指针;
通过第一种重载版本绑定了输出流,则返回绑定的该输出流;s
ostream* tie ( ) const;

关联后cout总是可以实时输出cin的内容,而不用等到程序结束
每当被“绑定”的对象有出入或输出操作，就会自动刷新“绑定”的对象的缓冲区，以达到实时的效果
*/
#include <iostream>
#include <fstream>
using namespace std;
 
int main () {
    ofstream ofs;
    ofs.open ("test.txt");

    // 每次按下回车键之后都会将本次输入的内容打印到test.txt文件中,
    // 注释掉就只有程序运行正常结束时才会将本次输入的内容全部一次性写到test.txt文件中.
    cin.tie(&ofs); //注释掉这一行试试看
    *cin.tie() << "There will be some text:";
    char c;
    while(cin >> c){
        ofs << c;
    }
    cin.tie(nullptr);
    ofs.close();

    return 0;
}