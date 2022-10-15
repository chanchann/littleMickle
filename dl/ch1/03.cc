#include <type_traits>

int main()
{
    std::remove_reference<int&>::type h1 = 3;
    std::remove_reference_t<int&> h2 = 3;
}