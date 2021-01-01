/*
如果派生类可能被用作基类，派生他最好使用关键字virtual
*/
/*
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

class Mammal :public virtual Animal
{
};

class Bird :public virtual Animal
{
};

class Reptile :public virtual Animal
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
	duckBilledP.age = 25;
	return 0;
}