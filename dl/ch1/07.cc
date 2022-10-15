template <int... Vals> 
struct IntContainer;

template <bool... Vals>
struct BoolContainer;

template <typename... Types>
struct TypeContainer;

template <template <typename> class... T>
struct TempalteContainer;

template <template <typename...> class...T>
struct TemplateContainer2;

// 这里都是声明，而没有定义
// 声明就已经包含编译器需要的所有信息了
// 尽在必要时才会引入定义

