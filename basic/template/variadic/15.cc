#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

namespace util {
template <typename ReturnType, typename... Args>
struct function_traits_defs {
  static constexpr size_t arity = sizeof...(Args);

  using result_type = ReturnType;

  template <size_t i>
  struct arg {
    using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
  };
};

template <typename T>
struct function_traits_impl;

template <typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(Args...)>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(*)(Args...)>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...)>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const&>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const&&>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) volatile>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) volatile&>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) volatile&&>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const volatile>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const volatile&>
    : function_traits_defs<ReturnType, Args...> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const volatile&&>
    : function_traits_defs<ReturnType, Args...> {};

template <typename T, typename V = void>
struct function_traits
    : function_traits_impl<T> {};

template <typename T>
struct function_traits<T, decltype((void)&T::operator())>
    : function_traits_impl<decltype(&T::operator())> {};

template <size_t... Indices>
struct indices {
  using next = indices<Indices..., sizeof...(Indices)>;
};
template <size_t N>
struct build_indices {
  using type = typename build_indices<N - 1>::type::next;
};
template <>
struct build_indices<0> {
  using type = indices<>;
};
template <size_t N>
using BuildIndices = typename build_indices<N>::type;

constexpr bool is_digit(char c) {
    return c <= '9' && c >= '0';
}

constexpr int stoi_impl(const char* str, int value = 0) {
    return *str ?
            is_digit(*str) ?
                stoi_impl(str + 1, (*str - '0') + value * 10)
                : throw "compile-time-error: not a digit"
            : value;
}

constexpr int mystoi(const char* str) {
    return stoi_impl(str);
}

// int main() {
//     static_assert(stoi("10") == 10, "...");
// }

template <typename T, typename U>  
T cast(U& s, U& t)
{
    if(t == "int")
    {
        return mystoi(s.c_str());
    }
    else 
    {
        return s;
    }
}

namespace details {
template <typename FuncType,
          typename VecType,
          size_t... I,
          typename Traits = function_traits<FuncType>,
          typename ReturnT = typename Traits::result_type>
ReturnT do_call(FuncType& func,
                VecType& args1,
                VecType& args2, 
           indices<I...> ) {
  assert(args1.size() >= Traits::arity);
  return func(args1[I]...);
}

}  // namespace details

template <typename FuncType,
          typename VecType,
          typename Traits = function_traits<FuncType>,
          typename ReturnT = typename Traits::result_type>
ReturnT unpack_caller(FuncType& func,
                VecType& args1,
                VecType& args2) {
  return details::do_call(func, args1, args2, BuildIndices<Traits::arity>());
}
}  // namespace util

int func(int a, int b, int c) {
  return a + b + c;
}

int func2(int a, int b) {
    return a * b;
}

void func3(int a, double b, std::string s)
{
    std::cout << a << " : " << b << s << std::endl;
}


int main() {
    // std::vector<int> args = {1, 2, 3};

    // int j = util::unpack_caller(func, args);
    // std::cout << j << std::endl;

    // std::vector<int> args2 = {2, 3};
    // int k = util::unpack_caller(func2, args2);
    // std::cout << k << std::endl;

    std::vector<std::string> a = {"123", "2.0", "mitsk"};
    std::vector<std::string> b = {"int", "double", "string"};
    util::unpack_caller(func3, a, b);
    return 0;
}