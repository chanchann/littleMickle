#include <iostream>
#include "Foo.h"
#include <pthread.h>

using namespace std;
class Test {
public:
    Test() {
        printf("constructing\n");
    }

    ~Test() {
        printf("destructing\n");
    }
};

void *threadFunc(void *arg) {
  const char *str = static_cast<const char *>(arg);
  printf("%s\n", str);
  Foo<Test>::instance();
	// Foo<Test>::destory();
  return NULL;  
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    const char* str = "In thread!!";
    pthread_create(&tid, NULL, threadFunc, (void*)str);
    pthread_join(tid, NULL);
        
    return 0;
}

