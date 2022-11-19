#include <type_traits>

template <typename TBooleanCont, typename TFunCont>
struct CompileSwitch_;

template <bool curBool, bool... TBools,
          template<typename...> class TFunCont,
          typename curFunc, typename... TFuncs>
struct CompileSwitch_<std::integer_sequence<bool, curBool, TBools...>, 
                    TFunCont<curFunc, TFuncs...>>
{
    static_asset((sizeof...(TBools) == sizeof...(TFuncs)) || (sizeof...(TBools) + 1 == sizeof...(TFuncs)));
    using type = typename std::conditional_t<curBool, >
}