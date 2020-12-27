// Copyright (c) 2020 by Chrono
//
// g++ string.cpp -std=c++11 -o a.out;./a.out
// g++ string.cpp -std=c++14 -o a.out;./a.out
// g++ string.cpp -std=c++14 -I../common -o a.out;./a.out
/*
C++ 支持多种字符类型，常用的 string 其实是模板类 basic_string 的特化形式；

目前 C++ 对 Unicode 的支持还不太完善，建议尽量避开国际化和编码转化，不要“自讨苦吃”；

应当把 string 视为一个完整的字符串来操作，不要把它当成容器来使用；

字面量后缀“s”表示字符串类，可以用来自动推导出 string 类型；

原始字符串不会转义，是字符串的原始形态，适合在代码里写复杂的文本；

处理文本应当使用正则表达式库 regex，它的功能非常强大，但需要花一些时间和精力才能掌握。

*/
#include <cassert>

#include <iostream>
#include <string>
#include <regex>

void case1() {
    using namespace std;

    string str = "abc";

    assert(str.length() == 3);
    assert(str < "xyz");
    assert(str.substr(0, 1) == "a");
    assert(str[1] == 'b');
    assert(str.find("1") == string::npos);
    assert(str + "d" == "abcd");
}

// c++14
void case2() {
    // 必须打开名字空间
    // 为了避免与用户自定义字面量的冲突，后缀“s”不能直接使用，必须用 using 打开名字空间才行，这是它的一个小缺点。
    using namespace std::literals::string_literals;

    using std::string;

    auto str = "std string"s; // 后缀s，表示是标准字符串，直接类型推导

    assert(str.length() > 0);

    assert("time"s.size() == 4); // 标准字符串可以直接调用成员函数
}

// 原始字符串
void case3() {
    using namespace std;

    auto str = R"(nier:automata)"; // 原始字符串：nier:automata
 
    auto str1 = R"(char""'')";  // 原样输出：char""''
    auto str2 = R"(\r\n\t\")";  // 原样输出：\r\n\t\"
    auto str3 = R"(\$)";        // 原样输出：\\\$
    auto str4 = "\\\\\\$";      // 转义后输出：\\\$

    auto str5 = R"==(R"(xxx)")==";  // 原样输出：R"(xxx)"

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
}

// 字符串转换函数
// boost中有lexical_cast 转换
void case4() {
    using namespace std;

    assert(stoi("42") == 42);   // 字符串转整数
    assert(stol("253") == 253L);    // 字符串转长整数
    assert(stod("2.0") == 2.0);     // 字符串转浮点数

    assert(to_string(1984) == "1984");  // 整数转字符串
}

// c++17
// c++11 实现的简单版本
// 注意data和c_str()区别，后者有\0
class my_string_view final {
private:
    const char* ptr = nullptr;
    size_t len = 0;
public:
    my_string_view() = default;
    ~my_string_view() = default;

    my_string_view(const std::string& str) noexcept
        : ptr(str.data()), len(str.length()) 
        {}
public:
    const char* data() const {
        return ptr;
    }

    size_t size() const {
        return len;
    }
};

// 正则表达式
// C++ 正则匹配有三个算法，注意它们都是“只读”的，不会变动原字符串。
// regex_match()：完全匹配一个字符串；
// regex_search()：在字符串里查找一个正则匹配；
// regex_replace()：正则查找再做替换。
static 
auto make_regex = [](const auto& txt) {  // 生产正则表达式
    return std::regex(txt);
};

static 
auto make_match = []() {  // 生产正则匹配结果
    return std::smatch();
};

void case5() {
    using namespace std;

    //using sregex = std::regex;
    //using cregex = std::regex;

    auto str = "neir:automata"s;

    auto reg  = make_regex(R"(^(\w+)\:(\w+)$)"); // 原始字符串定义正则表达式
    auto what = make_match();                   // 准备获取匹配的结果

    assert(regex_match(str, what, reg));    // 正则匹配,函数会返回 bool 值表示是否完全匹配正则。如果匹配成功，结果存储在 what 里，可以像容器那样去访问

    for(const auto& x : what) {
        cout << x << ',';
    }
    cout << endl;
}

void case6() {
    using namespace std;

    auto str = "god of war"s;

    auto reg  = make_regex(R"((\w+)\s(\w+))");
    auto what = make_match();

    auto found = regex_search(
                    str, what, reg);

    assert(found);
    assert(!what.empty());
    assert(what[1] == "god");
    assert(what[2] == "of");

    auto new_str = regex_replace(
        str,
        make_regex(R"(\w+$)"),
        "peace"
    );

    cout << new_str << endl;
}

// 在使用 regex 的时候，还要注意正则表达式的成本。
// 因为正则串只有在运行时才会处理，检查语法、编译成正则对象的代价很高，所以尽量不要反复创建正则对象，能重用就重用。
// 在使用循环的时候更要特别注意，一定要把正则提到循环体外。

// 还可以选择其他第三方正则库，比如PCRE,Hyoerscan, libsregex
int main() {
    // case1();
    // case2();
    // case3();
    // case4();
    case5();
    // case6();

    using namespace std;

    cout << "string demo" << endl;
}
