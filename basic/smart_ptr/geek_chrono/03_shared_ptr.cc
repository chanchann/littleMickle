/*
小心对象的析构函数，不要有非常复杂的，严重阻塞的操作
一旦shared_ptr在某个不确定的时间点析构释放资源，就会阻塞整个进程或者线程

class DemoShared final  // 危险的类
{
public:
    DemoShared() = default;
   ~DemoShared()  // 复杂的操作会导致shared_ptr析构时阻塞
   {
       // do some blocking thing ...
   }
};

*/