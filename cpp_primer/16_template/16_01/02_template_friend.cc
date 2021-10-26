

// 2. 如果一个非模板类包含一个模板友元，则所有友元实例被授权可以访问该类。

// 前置声明，在将模板的一个特定实例声明为友元时用到
template <typename T> 
class pal;

class C {
    friend class Pal<C>; //用类C实例化的Pal是C的一个友元
    //Pal2的所有实例都是C的友元，且无须前置声明
    template <typename T> friend class Pal2;
};

