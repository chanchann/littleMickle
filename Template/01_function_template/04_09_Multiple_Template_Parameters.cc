/*
有时 T 必须是一个引用，但返回类型是引用类型时可能出现问题，此时可以利用 std::decay去掉引用修饰符、cv 限定符等描述符，退化到最基本的类型
*/

#include <type_traits>
#include <iostream>

template<typename T, typename U, typename RT = std::decay_t<decltype(true ? T() : U())>>
RT max(T a, U b) {
    return b < a ? a : b;
}

/**
 * TODO 如何写example
 */