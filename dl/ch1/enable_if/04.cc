#include <type_traits>

// 以下几种方式等价

template<typename T>
std::enable_if_t<(sizeof(T) > 4), T>
foo() {
    return T();
}

template<typename T,
typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo1() {
}

template<typename T>
using EnableIfSizeGreater4 = std::enable_if_t<(sizeof(T) > 4)>;

template<typename T,
typename = EnableIfSizeGreater4<T>>
void foo2() {
}
