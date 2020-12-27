//car类以私有方式继承motor类，意思：汽车继承发动机的方法（函数）。
//倘若还有一个FuelCar类继承自Car类，那么不管两者之间是什么继承关系，FuelCar类都不能访问Motor类的方法。
#include <iostream>
using namespace std;

class Motor {
public:
	void SwitchIgnation() {
		cout << "Ignation on" << endl;
	}
	void PumpFuel() {
		cout << "Fuel in cylinders" << endl;
	}
	void FireCylinders() {
		cout << "Vrooom" << endl;
	}
};

class Car :private Motor { //private inheritance
public:
	void Move() {
		SwitchIgnation();
		PumpFuel();
		FireCylinders();
	}
};

int main() {
	Car myDreamCar;
	myDreamCar.Move();
	//myDreamCar.PumpFuel();//私有继承，不可访问。如果22行改为public，即可访问
	return 0;
}