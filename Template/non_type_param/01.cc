struct D
{
    operator double() { return 1.0; }
};

template <typename T>
double fun()
{
    T t;
    return t;
}

int main()
{
    double value = fun<D>();
    return 0;
}
