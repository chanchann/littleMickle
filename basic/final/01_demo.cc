/*
可以使用 final 关键字指定无法在派生类中重写的虚函数。
您还可以使用它指定无法继承的类。

class BaseClass {
  virtual void func() final;
};
 
class DerivedClass: public BaseClass {
  virtual void func(); // compiler error: attempting to 
             // override a final function
};

class BaseClass final 
{
};
 
class DerivedClass: public BaseClass // compiler error: BaseClass is 
                   // marked as non-inheritable
{
};

*/

