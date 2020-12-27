/*
覆盖的一种极端情况，Tuna.Swim() 可能异常Fish::Swim()的所有重载版本
*/
#include <iostream>
using namespace std;

class Fish {
public:
	void Swim() {
		cout << "fish swim ... !" << endl;
	}

	void Swim(bool isFreshWaterFish) { //overloaded version
		if (isFreshWaterFish)
			cout << "Swim in lake" << endl;
		else
			cout << "swim in sea" << endl;
	}
};

class Tuna :public Fish {
public:
    // solution 1 
    // using Fish::Swim;
	void Swim() {
		cout << "Tuna swims real fast" << endl;
	}
    // Solution 3, 覆盖所有方法
    // void Swim(bool isFreshWaterFish) {
    //     Fish::Swim(isFreshWaterFish);
    // }
};

int main() {
	Tuna mydinner;
	cout << "about my food" << endl;
	mydinner.Swim();
    // mydinner.Swim(false);    // Fish::Swim(bool) is hidden by Tuna::Swim()
	// solution 2
    mydinner.Fish::Swim(false);

	return 0;
}