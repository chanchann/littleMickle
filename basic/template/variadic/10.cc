#include <iostream>
#include <vector>

using namespace std;

template <std::size_t... Indices>
struct indices {
    using next = indices<Indices..., sizeof...(Indices)>;
};

template <std::size_t N>
struct build_indices {
    using type = typename build_indices<N-1>::type::next;
};

template <>
struct build_indices<0> {
    using type = indices<>;
};
template <std::size_t N>
using BuildIndices = typename build_indices<N>::type;

template <size_t num_args>
struct unpack_caller
{
private:
    template <typename FuncType, size_t... I>
    void call(FuncType &f, std::vector<int> &args, indices<I...>){
        f(args[I]...);
    }

public:
    template <typename FuncType>
    void operator () (FuncType &f, std::vector<int> &args){
        assert(args.size() == num_args); // just to be sure
        call(f, args, BuildIndices<num_args>{});
    }
};


int main()
{
    std::vector<int> a = {12,4,3,2};
    auto func = [](int i) { std::cout << i << std::endl; };    

    const size_t a_size = a.size();
    unpack_caller<4>(func, a);
}

