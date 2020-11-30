#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

/*
mem_fn既可以用于指针、引用，还可以用于对象本身
*/

class Employee
{
public:
    int DoSomething() {
        std::cout << "do something" << std::endl;
        return 0;
    }
    void OneParameter(int i) {
        std::cout << i << std::endl;
    }
};

// 定义一个全局的仿函数，使用STL中的for_each的用法也是司空见惯的,如：
int GiveDoSomething(Employee& e) {
    return e.DoSomething();
}

int main() {
    std::vector<Employee> emps_obj;
    emps_obj.push_back(Employee());
    emps_obj.push_back(Employee());
    emps_obj.push_back(Employee());
    // 初学者调用
    for (auto it = emps_obj.begin(); it!= emps_obj.end(); it++) {
        (*it).DoSomething();
    }

    std::cout << " -- global function -- " << std::endl; 
    std::for_each(emps_obj.begin(), emps_obj.end(), &GiveDoSomething);

    // mem_fn
    std::cout << " -- mem_fn -- " << std::endl; 
    std::for_each(emps_obj.begin(), emps_obj.end(), std::mem_fn(&Employee::DoSomething));

    // pass pointer
    std::vector<Employee*> emps_ptr;

    emps_ptr.push_back(new Employee());
    emps_ptr.push_back(new Employee());
    emps_ptr.push_back(new Employee());
    // mem_fn
    std::cout << " -- mem_fn pointer-- " << std::endl; 
    std::for_each(emps_ptr.begin(), emps_ptr.end(), std::mem_fn(&Employee::DoSomething));

    // pass one parameter
    // 如果成员函数接受额外参数（不仅仅是对象本身）, 那么mem_fn就无能为力了，要用bind 
    std::cout << " -- pass one parameter -- " << std::endl; 
    // std::for_each(emps_ptr.begin(), emps_ptr.end(), std::mem_fn(&Employee::OneParameter, 1);
    std::for_each(emps_ptr.begin(), emps_ptr.end(), std::bind(&Employee::OneParameter, std::placeholders::_1, 1));

    // continue
    // https://blog.csdn.net/elloop/article/details/50375820?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param
    // lambda
    // 自身
    // 回收ptr
    return 0;



}



