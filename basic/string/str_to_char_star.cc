#include <string>
#include <iostream>

void test01() {
    std::string s = "some string";
    char* cs = &s[0];
    std::cout << cs << std::endl;
    for(int i = 0; i < s.size(); i++) {
        cs[i] = '1';
    }
    std::cout << s << std::endl;
}
void test02() {
    std::string s = "";
    char* cs = &s[0];
    for(int i = 0; i < s.size(); i++) {
        cs[i] = '1';
    }
    std::cout << s << std::endl;
}
void test03() {
    std::string s = "some string";
    char* cs = &*s.begin();
    std::cout << cs << std::endl;
    for(int i = 0; i < s.size(); i++) {
        cs[i] = '1';
    }
    std::cout << s << std::endl;
}

void test04() {
    std::string s = "";
    char* cs = &*s.begin();
    std::cout << cs << std::endl;
    for(int i = 0; i < s.size(); i++) {
        cs[i] = '1';
    }
    std::cout << s << std::endl;
}

void test05() {
    std::string s = "some string";
    char* cs = const_cast<char*>(s.c_str());
    std::cout << cs << std::endl;
    for(int i = 0; i < s.size(); i++) {
        cs[i] = '1';
    }
    std::cout << s << std::endl;
}
void test06() {
    std::string s = "";
    char* cs = const_cast<char*>(s.c_str());
    std::cout << cs << std::endl;
    for(int i = 0; i < s.size(); i++) {
        cs[i] = '1';
    }
    std::cout << s << std::endl;
}

void test07() {
    std::string s = "some string";
    for(int i = 0; i < s.size(); i++) {
        s[i] = '1';
    }
    std::cout << s << std::endl;
}


int main() {
    std::cout << "test01" << std::endl;
    test01();
    std::cout << "test02" << std::endl;
    test02();
    std::cout << "test03" << std::endl;
    test03();
    std::cout << "test04" << std::endl;
    test04();
    std::cout << "test05" << std::endl;
    test05();
    std::cout << "test06" << std::endl;
    test06();
    std::cout << "test07" << std::endl;
    test07();
}