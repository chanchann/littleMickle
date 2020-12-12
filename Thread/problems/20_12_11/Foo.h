#ifndef FOO_H
#define FOO_H
#include <iostream>
#include <pthread.h>

template<typename T>
class Foo{
public:
	static T& instance() {
		pthread_key_create(&pkey_, &Foo::destory); 
    	if (!t_value_) {
			t_value_ = new T();
			printf("after constructed, t_value_ is %p\n", t_value_); 
		}
		assert(pthread_getspecific(pkey_) == NULL);
      	pthread_setspecific(pkey_, t_value_);
		return *t_value_;
  	}
	  
	static void destory(void* obj) {
		printf("before deleted, t_value_ is %p\n", t_value_); 
		delete t_value_;
		printf("t_value_ is deleted!!!\n");
	}
private:
	static __thread T* t_value_;
	static pthread_key_t pkey_;
};

template<typename T>
__thread T* Foo<T>::t_value_ = 0;

template<typename T>
pthread_key_t Foo<T>::pkey_ = 0;
#endif
