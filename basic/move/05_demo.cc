/*
右值引用和std::move的应用场景

1 实现移动语义

右值引用和std::move被广泛用于在STL和自定义类中实现移动语义，避免拷贝，从而提升程序性能

在没有右值引用之前，一个简单的数组类通常实现如下，有构造函数、拷贝构造函数、赋值运算符重载、析构函数等


// 例1：Array用法
int main(){
    Array a;
 
    // 做一些操作
    .....
     
    // 左值a，用std::move转化为右值
    Array b(std::move(a));
}


*/

#include <iostream>
class Array {
public:
    Array(int size) : size_(size) {
        data_ = new int[size_];
        std::cout << "constructor" << std::endl;
    }
     
    // 深拷贝构造
    Array(const Array& temp_array) {
        size_ = temp_array.size_;
        data_ = new int[size_];
        for (int i = 0; i < size_; i ++) {
            data_[i] = temp_array.data_[i];
        }
        std::cout << "copy constructor" << std::endl;
    }
     
    // 深拷贝赋值
    Array& operator=(const Array& temp_array) {
        delete[] data_;
 
        size_ = temp_array.size_;
        data_ = new int[size_];
        for (int i = 0; i < size_; i ++) {
            data_[i] = temp_array.data_[i];
        }
        std::cout << "copy assign " << std::endl;
    }
    // 优雅
    // 移动构造函数
    Array(Array&& temp_array) {
        data_ = temp_array.data_;
        size_ = temp_array.size_;
        // 为防止temp_array析构时delete data，提前置空其data_      
        temp_array.data_ = nullptr;
    }
    ~Array() {
        delete[] data_;
        std::cout << "desconstructor" << std::endl;
    }
 
public:
    int *data_;
    int size_;
};
