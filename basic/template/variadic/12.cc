#include <tuple>

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

namespace details {
template <typename FuncType,
          typename VecType,
          size_t... I,
          typename Traits = function_traits<FuncType>,
          typename ReturnT = typename Traits::result_type>
ReturnT do_call(FuncType& func,
                VecType& args,
           indices<I...> ) {
  assert(args.size() >= Traits::arity);
  return func(args[I]...);
}
}  // namespace details

template <typename FuncType,
          typename VecType,
          typename Traits = function_traits<FuncType>,
          typename ReturnT = typename Traits::result_type>
ReturnT unpack_caller(FuncType& func,
                VecType& args) {
  return details::do_call(func, args, BuildIndices<Traits::arity>());
}
}  // namespace util

/*
NOTE: all types must be unique
*/
template<template<typename...> class Container, typename... Ts>
struct heterogeneous
{
	std::tuple<Container<Ts>...> containers;

	template<typename T>
	auto get() -> decltype(std::get<Container<T>>(containers))
	{
		return std::get<Container<T>>(containers);
	}
};

template<template<typename...> class Container, typename Key, typename... Ts>
struct heterogeneous_map
{
	std::tuple<Container<Key, Ts>...> containers;

	template<typename T>
	auto& get()
	{
		return std::get<Container<Key, T>>(containers);
	}
};


void func1(int a, int b) {
    std::cout << a << std::endl;
	std::cout << b << std::endl;
}

int main()
{
	heterogeneous<std::vector, int, float, std::string> hetero;
	hetero.get<int>().emplace_back(1);
	hetero.get<int>().push_back(2);
	// hetero.get<float>().emplace_back(1.5f);
	// hetero.get<std::string>().emplace_back("hello");
	// hetero.get<std::string>().emplace_back("world");

	
	// std::apply([](auto ...x)
	// {
	// 	auto print = [](auto const& container) {
	// 		for (auto const& e : container)
	// 			std::cout << e << std::endl;
	// 	};

	// 	(print(x),...);
	// }, hetero.containers);
	// util::unpack_caller(func1, hetero);

}




