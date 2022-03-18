## "Declare destructors virtual in polymorphic base classes"

```cpp
class TimeKeeper{                              //计时器类，用来当做基类
  public:
    TimeKeeper();                              //这是构造函数
    ~TimeKeeper();                             //这是析构函数
  ......
};

class AtomicClock : public TimeKeeper{...};   //原子钟是一种计时器
class WaterClock : public TimeKeeper{...};    //水钟也是一种计时器

TimeKeeper* getTimeKeeper(){...}              //用来返回一个动态分配的基类对象
TimeKeeper* ptk = getTimeKeeper();            
.....                                         //使用这个指针操作它的子类
delete ptk;                                   //使用完毕，释放资源
```

## 多态的三个条件

1. 要有继承

2. 要有虚函数重写

3. 用父类指针（父类引用）指向子类对象

## 问题所在

getTimeKeeper返回的指针指向一个derived class对象, 但是对象经由一个base class指针删除，而base class有个non-virtual析构函数。

导致derived部分没有被销毁。

## 解决办法

给base classs一个virtual析构函数

## virtual相关

1. virtual函数的目的是允许derived class的实现定制化

2. 任何class只要带有virtual函数几乎确定应该有一个virtual析构函数

3. 不含virtual通常表示并不意图作为base class

4. 胡乱设置virtual，会导致无端插入vptr(体积膨胀, 传递其他语言带来的问题...)

## pure virtual

如果希望拥有抽象class，但是没有函数需要设置成pure virtual？ ==> 将析构函数设置成pure virtual

## 总结

1. 多态性质的base class应该声明virtual析构函数

2. class带有virtual函数，应该拥有一个virtual析构函数

3. class的涉及目的不是作为base class使用，或不是为了具备多态性，就不该设置virtual析构函数

## 相关阅读

https://blog.csdn.net/lihao21/article/details/50688337