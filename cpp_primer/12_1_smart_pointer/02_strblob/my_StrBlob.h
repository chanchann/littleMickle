/*
exercise 12.2

string& StrBlob::front() const 只在后面加const也是重载
*/

#ifndef MY_STRBLOB_H 
#define MY_STRBLOB_H 

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>
using namespace std;


class StrBlob {
public:
    typedef vector<string>::size_type size_type;

	// constructors
    StrBlob();
    StrBlob(initializer_list<string> il);

	// size operations
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();

    // element access
    string& front();
    string& back();
    // overload
    // const string& front() const;
    // const string& back() const;
    string& front() const;
    string& back() const;

private:
    shared_ptr<vector<string>> data; 
    // throws msg if data[i] isn't valid
    void check(size_type i, const string &msg) const;
};



StrBlob::StrBlob() : data(make_shared<vector<string>>()) { }


StrBlob::StrBlob(initializer_list<string> il): 
              data(make_shared<vector<string>>(il)) { }

void StrBlob::check(size_type i, const string &msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

string& StrBlob::front() {
	// if the vector is empty, check will throw
	check(0, "front on empty Blob");
	return data->front();
}

string& StrBlob::back() {
	// if the vector is empty, check will throw
	check(0, "back on empty Blob");
	return data->back();
}

string& StrBlob::front() const {
	// if the vector is empty, check will throw
	check(0, "front on empty Blob");
	return data->front();
}

string& StrBlob::back() const {
	// if the vector is empty, check will throw
	check(0, "back on empty Blob");
	return data->back();
}

void StrBlob::pop_back() {
	// if the vector is empty, check will throw
	check(0, "pop_back on empty Blob");
	return data->pop_back();
}









#endif	// MY_STRBLOB_H
