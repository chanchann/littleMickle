//将Fish::Swim()声明为虚函数带来的影响.在这里多态就是，将派生类对象视为基类对象，并执行派生类的Swim()实现
#include <iostream>
using namespace std;

class Fish {
public:
	virtual void Swim() {
		cout << "Fish swim" << endl;
	}
};

class Tuna :public Fish {
public:
	void Swim() {
		cout << "Tuna swim" << endl;
	}
};

class Carp :public Fish {
public:
	void Swim() {
		cout << "Carp swim" << endl;
	}
};

void MakeFishSwim(Fish& inputFish) {
	inputFish.Swim();
}

int main() {
	Tuna mydinner;
	Carp mylunch;

	MakeFishSwim(mydinner);
	MakeFishSwim(mylunch);

	return 0;
}
