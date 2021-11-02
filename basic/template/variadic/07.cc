#include <iostream>

template<typename T>
void Print(T arg) { std::cout << arg << ", " << std::endl; }

template<typename T, typename... Ts>
void Print(T arg1, Ts... arg_left){
    std::cout << arg1 << ", ";
    Print(arg_left...);
}

int main(int argc, char** argv)
{
    Print(719,7030,"civilnet");
}
