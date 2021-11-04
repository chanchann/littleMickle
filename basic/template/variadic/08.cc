#include <iostream>
using namespace std;

void func()
{
   cerr << "EMPTY" << endl;
}

template <class ... B>
typename std::enable_if<sizeof...(B) == 0>::type func()
{
}

template <class A, class ...B> void func()
{
   cerr << "A: "  << typeid(A).name() << endl;
   func<B... >(); // line A
}


int main(void)
{
   func();           // This outputs EMPTY
   func<int,int>();  // This will not output EMPTY
   return 0;
}
