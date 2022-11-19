/*
constexpr表示这玩意儿在编译期就可以算出来（前提是为了算出它所依赖的东西也是在编译期可以算出来的

而const只保证了运行时不直接被修改（但这个东西仍然可能是个动态变量）。

这其实是一个遗留的命名问题，简单说const其实是readonly，constexpr才是const。
*/

template<int N> class C{};

constexpr int FivePlus(int x) {
  return 5 + x;
}

void f(const int x) {
//   C<x> c1;            // Error: x is not compile-time evaluable.
  C<FivePlus(6)> c2;  // OK
}