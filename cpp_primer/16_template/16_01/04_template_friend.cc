// 类模板与友元模板(多对多关系)

template <typename T>
class C2 {
    //Pal3的所有实例都是C2的每个实例的友元，同样不需要前置声明
    template <typename X> friend class Pal3;
};

// 令模板自己的类型参数成为友元
// 对于某个类型名Foo，Foo将成Bar<Foo>的友元。

template <typename Type> class Bar {
friend Type; //将访问权限授予用来实例化Bar的类型
};
