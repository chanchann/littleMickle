/*
在C++11中，emplace_back直接通过参数构造对象至容器中，不需要拷贝或者移动

对比下效率

但我结果，emplace_back要慢点???? ???
*/

#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;


const int num = 100000;

class timer {
public:
	clock_t start;
	clock_t end;
	string name;
	timer(string n) {
		start = clock();
		name = n;
	}
	~timer() {
		end = clock();
		printf("%s time: %f \n", name.c_str(), 
			(end - start) * 1.0 / CLOCKS_PER_SEC * 1000);
	}
};

 
struct President {
    std::string name;
    std::string country;
    int year;
 
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
        // std::cout << "I am being constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year) {
        // std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

void test_emplace_back(int count) {
    std::cout << "emplace_back test:\n";
    {
        std::vector<President> elections;
        timer t("emplace_back");
        for (int i = 0; i < count; ++i) {
            elections.emplace_back("test emplace_back", "test emplace_back", 1994 + i);
        }
    }
}

void test_push_back(int count) {
    std::cout << "push_back:\n";
    {
        std::vector<President> reElections;
        timer t("push_back");
        for (int i = 0; i < count; ++i) {
            reElections.push_back(President("test push_back", "test push_back", 1994 + i));    
        }
    }
}


int main() {
    int count = 1000000;
    test_emplace_back(count);
    test_push_back(count);

}
