/*
在正常使用时function 主要会用来存储可调用的对象，如函数指针、可调用类、类成员函数、lambda等. 
*/

#include <functional>
#include <iostream>

int getOne() {
    return 1;
}

struct getTwo {
    getTwo() {}
    int operator()() {
        return 2;
    }
};

class getNumber {
public:
    int getThree() {
        return 3;
    }
    static int getFour() {
        return 4;
    }
};

int main() {
    // basic function
    std::function< int() > getNumber(getOne);
    std::cout << getNumber() << std::endl;

    // class which override operator()
    std::function< int() > getNumber2(getTwo{});
    std::cout << getNumber2() << std::endl;

    // non static member function
    class getNumber n;
    std::function< int(class getNumber *) > getNumber3 = &getNumber::getThree;
    std::cout << getNumber3(&n) << std::endl;

    std::function< int(class getNumber *) > getNumber4 = std::bind(&getNumber::getThree, &n);
    std::cout << getNumber4(&n) << std::endl;

    std::function< int(class getNumber *) > getNumber5(&getNumber::getThree);
    std::cout << getNumber5(&n) << std::endl;

    // static member function
    std::function< int() > getNumber6(&getNumber::getFour);
    std::cout << getNumber6() << std::endl;
    return 0;
}