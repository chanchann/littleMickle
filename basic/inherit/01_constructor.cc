/*
基类初始化，向基类传递参数

*/

//包含初始化列表的派生类构造函数
#include <iostream>
using namespace std;

class Fish {
protected:
	bool isFreshWaterFish;
public:
	//Fish构造函数
	Fish(bool isFreshWater) :isFreshWaterFish(isFreshWater) {}
	void swim() {
		if (isFreshWaterFish)
			cout << "swim in lake" << endl;
		else
			cout << "swim in sea" << endl;
	}
};

class Tuna :public Fish {
public:
	Tuna() :Fish(true) {}//构造函数初始化
};

class Carp :public Fish {
public:
	Carp() :Fish(false) {}//构造函数初始化
};

int main() {
	Tuna mylunch;
	Carp mydinner;

	cout << "here are my food:"<<endl;
	cout << "my lunch: ";
	mylunch.swim();
	cout << "my dinner: ";
	mydinner.swim();

	return 0;
}