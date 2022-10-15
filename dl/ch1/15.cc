// 非完全特化的类模版中引入完全特化的分支代码是非法的

template <typename TW>
struct Wrapper
{
    template <typename T>
    struct Fun_ 
    {
        constexpr static size_t value = 0;
    };
    
    // invalid
    template <>
    struct Fun_<int>
    {
        constexpr static size_t value = 1;
    };
};

// 为了解决这个问题，我们使用部分特化来代替完全特化
template <typename TW>
struct Fix
{
    template <typename T, typename TDdummy = void>
    struct Fun_
    {
        constexpr static size_t value = 0;
    }; 

    template <typename TDummy>
    struct Fun_<int, TDummy>
    {
        constexpr static size_t value = 1;
    }
};