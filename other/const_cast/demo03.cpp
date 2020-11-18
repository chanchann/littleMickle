/*
3. It is undefined behavior to modify a value which is initially declared as const. 

But the problem didn't occur.
Why?


*/

#include <iostream> 
using namespace std; 

int fun(int* ptr) { 
    printf("in fun : ptr address : %p\n", ptr);

	*ptr = *ptr + 10; 
    printf("in fun : *ptr : %d\n", *ptr);
    printf("in fun : ptr address : %p\n", ptr);

	return (*ptr); 
} 

int main(void) { 
    // It it fine to modify a value which is not initially declared as const. 
    // int val = 10;
	const int val = 10; 
    printf("val address : %p\n", &val);
	const int *ptr = &val; 
    printf("ptr address : %p\n", ptr);

	int *ptr1 = const_cast <int *>(ptr); 

    printf("ptr1 address : %p\n", ptr1);

	cout << "return : " << fun(ptr1) << endl; 
	cout << "val : " << val << endl;; 
	return 0; 
} 
