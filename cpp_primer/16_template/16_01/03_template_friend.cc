// 类模板与普通友元

template <typename T>
class C2 {
    //Pal2是一个非模板类，它是C2所有实例的友元，不需要前置声明
    friend class Pal2;
};
