/*
浅拷贝
*/

#include <iostream>
#include <cstring>
using namespace std;

class String {  
public:  
    String(const char *pStr = "") {  
        if(NULL == pStr) {  
            pstr = new char[1];  
            *pstr = '\0';  
        }  
        else {  
            pstr = new char[strlen(pStr)+1];  
            strcpy(pstr,pStr);  
        }  
    }  
      
    String(const String &s)  
        :pstr(s.pstr) 
    {}  
      
    String& operator=(const String&s) {  
        if(this != &s) {  
            delete[] pstr; 
            pstr = s.pstr;
        }   
        return *this;  
    }  
      
    ~String() {  
        if(NULL != pstr) {  
            delete[] pstr;  
            pstr = NULL;
        }   
    }   
    friend ostream& operator<<(ostream & _cout, const String &s) {  
        _cout << s.pstr;  
        return _cout;  
    }  
private:  
    char *pstr;       
}; 

int main() {     
    String s1("sss");  
    String s2(s1);  
    String s3(NULL);  
    s3 = s1;  
    cout << s1 << endl;  
    cout << s2 << endl;  
    cout << s3 << endl;  
    return 0;  
} 