/*
返回类型的重载可能导致调用的歧义
*/

template <typename T, typename U>
auto max(T a, U b) {
  return b < a ? a : b;
}

template <typename RT, typename T, typename U>
RT max(T a, U b) {
  return b < a ? a : b;
}

int main() {
    auto a = ::max(1, 3.14);               // 调用第一个模板
    auto b = ::max<long double>(3.14, 1);  // 调用第二个模板
    // auto c = ::max<int>(1, 3.14);          // 错误：两个模板都匹配
    // 模板一为double max<int, double>, 模板二为int max<int, double>
}

