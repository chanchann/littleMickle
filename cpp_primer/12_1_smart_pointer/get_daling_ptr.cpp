/**
 * @brief  
 * .get()造成的悬垂指针问题
 * @note   
 * 不要保存p.get()的返回值 
 * 无论是保存为裸指针还是shared_ptr都是错误的 
 * 保存为裸指针不知什么时候就会变成空悬指针 
 * 保存为shared_ptr则产生了独立指针
 * 不要delete p.get()的返回值 
 * 会导致对一块内存delete两次的错误
 * @retval None
 */


#include <iostream>
#include <memory>

using namespace std;

void process(shared_ptr<int> p){
	cout<< "In process, use_count is " << p.use_count() << endl;
    cout << "In process p :" << p << endl;
}

int main(){
	shared_ptr<int> p(new int(42));
	cout<< "Before process, use_count is " << p.use_count() << endl;
	cout<< "Before process, p is " << p << endl;

	process(shared_ptr<int>(p));
	cout<< "After process, use_count is " << p.use_count() << endl;

	cout<< "After process, p refers to " << *p << endl;
	
	/* 12.2 
	 * when main() ends, error: pointer being freed was not allocated 
	 * because when process() ended, the ptr is destroyed, thus the memory pointed by p is destroyed
	 * and then p became a dangling pointer */
	cout<< "Before process using p.get(), use_count is " << p.use_count() << endl;

	process(shared_ptr<int>(p.get()));
	cout<< "After process using p.get(), use_count is " << p.use_count() << endl;

	cout<< "After process using p.get(), p refers to " << *p << endl;
	
	cout<< "Now p is a dangling pointer, make it point NULL... " << endl;
	p = nullptr;

	return 0;
}

