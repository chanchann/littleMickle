/*
当const在函数名前面的时候修饰的是函数返回值。

当const在函数名后面表示是常成员函数，该函数不能修改对象内的任何成员，只能发生读操作，不能发生写操作。 

*/

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;

	// constructors
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
    StrBlob(std::initializer_list<std::string> il);

	// size operations
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();

    // element access
    std::string& front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data; 
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};


// constructor
inline
StrBlob::StrBlob(std::initializer_list<std::string> il): 
              data(std::make_shared<std::vector<std::string>>(il)) { }

inline 
void StrBlob::check(size_type i, const std::string &msg) const {
	if (i >= data->size())
		throw std::out_of_range(msg);
}
inline 
std::string& StrBlob::front() {
	// if the vector is empty, check will throw
	check(0, "front on empty Blob");
	return data->front();
}

inline 
std::string& StrBlob::back() {
	// if the vector is empty, check will throw
	check(0, "back on empty Blob");
	return data->back();
}

inline 
void StrBlob::pop_back() {
	// if the vector is empty, check will throw
	check(0, "pop_back on empty Blob");
	return data->pop_back();
}

int main() {
    // const StrBlob csb{"hello", "world", "111"};
    StrBlob sb{"hello", "world", "222"};

    // std::cout << csb.front() << " " << csb.back() << std::endl;
    sb.back() = "333";
    std::cout << sb.front() << " " << sb.back() << std::endl;
}




