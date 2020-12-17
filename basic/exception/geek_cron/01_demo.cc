
#include <iostream>
#include <stdexcept>

using namespace std;

class my_exception : public std::runtime_error {
public:
    using this_type     = my_exception;
    using super_type    = std::runtime_error;
public:
    my_exception(const char* msg):
        super_type(msg)
    {}

    my_exception() = default;
    ~my_exception() = default;
private:
    int code = 0;
};


// 抛异常的时候，不要直接用throw关键字，封装成一个函数
// 通过引入一个中间层来获取更多可读性，安全性和灵活性
// 抛异常的函数不会有阀返回值，这里用“属性”做编译阶段优化
[[noreturn]]
void raise(const char* msg) {
    throw my_exception(msg);
    //throw runtime_error(msg);
}

// 建议只写一个catch块
// 这里是function try ， 函数名后直接写try块
// catch块于函数体同级并列
void case1()
try {
    raise("error occured");
} catch(const exception& e) {  // 这里写const & 避免拷贝代价 ，可以用于基类
    cout << e.what() << endl;  // what()是exception的虚函数
}

void case2() noexcept {
    cout << "noexcept" << endl;
}

void case3() noexcept {
    throw "Oh My God";
}

int main() {
    case1();
    case2();
    // case3();

    cout << "exception demo" << endl;
}
