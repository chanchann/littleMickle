#include <iostream>

class Example {
public:
    Example() = default;
    Example(const Example&);
private:
    int data;
};

Example::Example(const Example& ex) = default;

int main() {
    Example e;
    return 0;
}