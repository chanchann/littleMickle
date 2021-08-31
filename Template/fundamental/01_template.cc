#include <iostream>

// template function
template <typename T>
T square(T x) {
    return x*x;
}

// template class
template<typename T>
class BoVector {
public:  
    BoVector() : size_(0) {}
    void push(T x) {
        arr_[size_] = x;
        size_++;
    }
    void print() const {
        for(int i = 0; i < size_; i++) {
            std::cout << arr_[i] << std::endl;
        }
    }
    T get(int i) const {
        // check bound first
        return arr_[i];
    }
    int getSize() const {
        return size_;
    }

private:
    T arr_[1000];
    int size_;
};


template<typename T> 
BoVector<T> operator*(const BoVector<T>& rhs1, const BoVector<T>& rhs2) {
    BoVector<T> ret;
    if(rhs1.getSize() != rhs2.getSize()) return ret;  // not properly process yet
    for(int i = 0; i < rhs1.getSize(); i++) {
        ret.push(rhs1.get(i) * rhs2.get(i));
    }
    return ret;
}

int main() {
    // Why we need template
    // Cause Code bloat
    std::cout << square<int>(5) << std::endl;
    std::cout << square(5) << std::endl;

    std::cout << square<double>(5.5) << std::endl;
    std::cout << square(5.5) << std::endl;
    // !! function template can infer the type by parameter data type 
    // !! class template have to specify the data type
    BoVector<int> bv;
    bv.push(2);
    bv.push(4);
    bv.push(5);
    bv.push(9);
    bv.print();

    std::cout << "print square bv" << std::endl;
    bv = square(bv);  
    bv.print();
}