/*
模板被编译两次，分别发生在实例化前和实例化期间
实例化前检查模板代码本身，包括
检查语法是否正确，如是否遗漏分号
发现使用不依赖于模板参数的 unknown name（类型名、函数名......）
检查不依赖于模板参数的 static assertion
实例化期间，再次检查模板代码保证所有代码有效（如某个类型不支持 operator<），特别的是，会再次检查依赖于模板参数的部分

*/

template <typename T>
void f(T x) {
  undeclared();   // first-phase compile-time error if undeclared() unknown
  undeclared(x);  // second-phase compile-time error if undeclared(T) unknown
  static_assert(sizeof(int) > 10,
                "int too small");  // always fails if sizeof(int) <= 10
  static_assert(sizeof(T) > 10,
                "T too small");  // fails if instantiated for T with size <= 10
}

