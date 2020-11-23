/*
1. const_cast can be used to change non-const class members inside a const member function.


*/

#include <iostream> 
using namespace std; 

class student { 
private: 
	int roll; 
public: 
	// constructor 
	student(int r) : roll(r) {} 

	// A const function that changes roll with the help of const_cast 
    //  Inside const member function fun(), 
    // ‘this’ is treated by the compiler as ‘const student* this’,
	void fun() const { 
		( const_cast <student*> (this) )->roll = 5; 
        // this->roll = 5; // expression must be a modifiable lvalueC/C++(137)

	} 
	int getRoll() { return roll; } 
}; 

int main(void) { 
	student s(3); 
	cout << "Old roll number: " << s.getRoll() << endl; 

	s.fun(); 

	cout << "New roll number: " << s.getRoll() << endl; 

	return 0; 
} 
