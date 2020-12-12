/*
以下两种情形都将发生线程类对象的移动操作:

//返回thread参数
std::thread get_thread()
{
    //方式一：
    //return  std::thread (do_fun, 100);

    //方式二：
    std::thread td(do_fun, 100);
    return td;
}

//传递thread参数
void move_thread(std::thread td)
{
}

当一个std::thread对象执行移动操作后，线程的所有权将发生转移，
原有线程对象的相关标识被清空，失去线程的控制权。其原有线程类对象ID变为0，joinable变为为false。

*/

#include <iostream>
#include <thread>
#include <memory>

void do_fun(int num) {
    ++num;
}

int main(int argc, char* argv[]) {
    int num = 10;
    //原有对象
    std::thread task(do_fun, num);
    std::cout << "before call move task thread id is " << task.get_id() << std::endl;
    std::cout << "before call move task thread joinable status is " << task.joinable() << std::endl;
    
	//发生移动操作
    std::thread move_task = std::move(task);
  
    std::cout << "\nafter call move task thread id is " << task.get_id() << std::endl;
    std::cout << "after call move task thread  joinable status is " << task.joinable() << std::endl;

    std::cout << "\nmove_task  thread id is " << move_task.get_id() << std::endl;
    std::cout << "move_task thread joinable status is " << move_task.joinable() << std::endl;

    //如果joinable为false, 调用join 程序异常,
    //移动后task对象的joinable为false
    if (task.joinable()) {
        task.join();
        std::cout << "call task  member function " << std::endl;
    }

    //如果joinable为false, 调用join 程序异常
    if (move_task.joinable()) {
        move_task.join();
        std::cout << "call move_task  member function " << std::endl;
    }
}