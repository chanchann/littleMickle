// enable_if

template <bool B, typename T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T>
{
    using type = T;
};

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

// substitution failure is not an error (SFINAE)
// 增强重载

template <bool IsFeedbackOut, typename T, enable_if_t<IsFeedbackOut>* = nullptr>
auto FeedbackOut_(T &&) { std::cout << "111" << std::endl; }

template <bool IsFeedbackOut, typename T, enable_if_t<!IsFeedbackOut>* = nullptr>
auto FeedbackOut_(T &&) { std::cout << "222" << std::endl; }
