// ------------- UTILITY---------------
template<int...> struct index_tuple{}; 

template<int I, typename IndexTuple, typename... Types> 
struct make_indexes_impl; 

template<int I, int... Indexes, typename T, typename ... Types> 
struct make_indexes_impl<I, index_tuple<Indexes...>, T, Types...> 
{ 
    typedef typename make_indexes_impl<I + 1, index_tuple<Indexes..., I>, Types...>::type type; 
}; 

template<int I, int... Indexes> 
struct make_indexes_impl<I, index_tuple<Indexes...> > 
{ 
    typedef index_tuple<Indexes...> type; 
}; 

template<typename ... Types> 
struct make_indexes : make_indexes_impl<0, index_tuple<>, Types...> 
{}; 

 // ----------UNPACK TUPLE AND APPLY TO FUNCTION ---------
#include <tuple>
#include <iostream> 

using namespace std;

template<class Ret, class... Args, int... Indexes > 
Ret apply_helper( Ret (*pf)(Args...), index_tuple< Indexes... >, tuple<Args...>&& tup) 
{ 
    return pf( forward<Args>( get<Indexes>(tup))... ); 
} 

template<class Ret, class ... Args> 
Ret apply(Ret (*pf)(Args...), const tuple<Args...>&  tup)
{
    return apply_helper(pf, typename make_indexes<Args...>::type(), tuple<Args...>(tup));
}

template<class Ret, class ... Args> 
Ret apply(Ret (*pf)(Args...), tuple<Args...>&&  tup)
{
    return apply_helper(pf, typename make_indexes<Args...>::type(), forward<tuple<Args...>>(tup));
}

// --------------------- TEST ------------------

int func1(int i)
{
    std::cout << "function func1(" << i << ");\n";
    return i;
}

void func2(int i, double d)
{
    std::cout << "function func2(" << i << ", " << d << ");\n";
}

void func3(int i, double j, const char* s)
{
    std::cout << i << " " << j << " " << s << std::endl;
}

void func4(int i, double j, const char* s, const char *p)
{
    std::cout << i << " " << j << " " << s << p <<  std::endl;
}

template <typename T, typename Tuple>
auto push_front(const T& t, const Tuple& tuple) -> decltype(std::tuple_cat(std::make_tuple(t), tuple))
{
    return std::tuple_cat(std::make_tuple(t), tuple);
}

void test01()
{
    int d = apply(func1, std::make_tuple(2));    
 
    std::tuple<int, double> tup(23, 4.5);
    apply(func2, tup);   // tup : 23, 4.5

    // tup2 : 23, 4.5, "skmit"
    auto tup2 = std::tuple_cat(tup, std::make_tuple("skmit"));
    apply(func3, tup2);

    
    // auto tup4 = std::tuple_cat(tup2, std::make_tuple("zhangge"));
    auto tup4 = push_front("zhangge", tup2);
    apply(func4, tup4);
}

template <typename T> 
T cast(const std::string& val, const std::string& type)
{
    if(type == "int")
        return stoi(val);
    else if(type == "double")
    {
        return stod(val);
    }
    else
    {
        return val;
    }
}

void test02()
{
    std::vector<std::string> vec_a = {"123", "2.0"};
    std::vector<std::string> vec_b = {"int", "double"};

    for(int i =0; i < vec_a.size(); i++)
    {
        // cast 
        
    }
}

int main()
{


    

    return 0;
}


