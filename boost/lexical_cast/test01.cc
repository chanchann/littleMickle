#include <iostream>  
#include <boost/lexical_cast.hpp>  
  
using namespace std;  
using namespace boost;  
  
int main() {  
    string s = "123";  
    int a = lexical_cast<int>(s);  
    double b = lexical_cast<double>(s);  
  
    std::cout << a + 1 << std::endl;
    std::cout << b + 1 << std::endl;

    try {  
	//为了防止转化错误使用一个错误的例子
        int c = lexical_cast<int>("wrong_number");  
    }  
    catch(bad_lexical_cast & e) {  
        std::cout << e.what() << std::endl;
    }  
    return 0;
} 