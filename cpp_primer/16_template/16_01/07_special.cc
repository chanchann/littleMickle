#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class Compare {
public:
    bool equal(T a,T b);
};

template<class T>
bool Compare<T>::equal(T a, T b) {
    return a == b;
}

//模板全特化
template<>
class Compare<float> {
public:
    bool equal(float a, float b);
};

bool Compare<float>::equal(float a, float b) {
    return std::abs(a - b) < 10e-3;
}

int main() {
    Compare<int> C;
    cout << C.equal(1,2) << endl;
    Compare<float> C2;
    cout << C2.equal(1.001,1.001) << endl;
    return 0;
}