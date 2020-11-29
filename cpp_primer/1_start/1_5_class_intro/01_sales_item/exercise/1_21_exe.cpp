#include "Sales_item.h"
#include <iostream>

int main() {
    Sales_item item1, item2;
    std::cout << "Input the same ISBN items" << std::endl;
    std::cin >> item1 >> item2;
	// first check that item1 and item2 represent the same book
	if (compareIsbn(item1, item2)) {
    	std::cout << "ISBN , sales number, sales , mean " <<  item1 + item2 << std::endl;
	} else {
    	std::cout << "ISBN is different" << std::endl;
	}
    return 0;
}
