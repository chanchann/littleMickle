//使用虚继承解决菱形问题
//鸭嘴兽继承自鸟类 哺乳类 鱼类，而三者均继承自动物类
//以下程序测试对鸭嘴兽实例化时，将实例化多少个animal类
//每个Platuypus实例包含多少个基类animal的实例
/*
Constructed Animal
Constructed Animal
Constructed Animal
Platypus constructed
*/
#include <iostream>
using namespace std;

class Animal 
{
public:
	Animal()
	{
		cout << "Constructed Animal" << endl;
	}
	//sample member
	int age;
};

class Mammal :public Animal
{
};

class Bird :public Animal
{
};

class Reptile :public Animal
{
};

class Platypus :public Mammal, public Bird, public Reptile
{
public:
	Platypus()
	{
		cout << "Platypus constructed" << endl;
	}
};

int main()
{
	Platypus duckBilledP;
	//duckBilledP.age = 25;//会导致编译错误，因为确定设置的是Mammal::Animal::age、Bird::Animal::age 还是 Reptile::Animal::age
	return 0;
}