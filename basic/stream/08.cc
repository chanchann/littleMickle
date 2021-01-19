/*
https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html

注意

https://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable

*/

#include <iostream>   
#include <sstream>   
#include <thread>
#include <chrono>
using namespace std;  
  
int main(int argc,char *argv[]) {  
    std::stringstream stream;  
    string str; 
    int i = 0;
    while(i++ < 5) {     
        //clear()，这个名字让很多人想当然地认为它会清除流的内容。   
        //实际上，它并不清空任何内容，它只是重置了流的状态标志而已！   
        // stream.clear();    
  
        // 去掉下面这行注释，清空stringstream的缓冲，每次循环内存消耗将不再增加!   
        // stream.str("");     // 但是这里哈斯有问题,后面都为0
        
        // ou can clear the error state and empty the stringstream all in one line
        std::stringstream().swap(stream);    
  
        stream << "sdfsdfdsfsadfsdafsdfsdgsdgsdgsadgdsgsdagasdgsdagsadgsdgsgdsagsadgs";  
        stream >> str;     
  
        //测试输出每次循环，你的内存消耗增加了多少！   
        cout << "Size of stream = " << stream.str().length() << endl;  
        this_thread::sleep_for(chrono::seconds(1));
    }  
   
    return EXIT_SUCCESS;  
}  