#include <iostream>


void Print() {std::cout<<std::endl;}

template<typename T, typename... Ts>
void Print(T arg1, Ts... arg_left){
    std::cout<<arg1<<", ";
    Print(arg_left...);
}

int main()
{
    Print(719,7030,"civilnet");
}
