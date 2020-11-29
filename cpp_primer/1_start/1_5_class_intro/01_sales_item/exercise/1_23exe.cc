#include <iostream>
#include "Sales_item.h"

int main()  {
    Sales_item total, trans; 
    int num = 1;
    std::cout << "Please input some trans records ..." << std::endl; 
    // read the first transaction and ensure that there are data to process
    if (std::cin >> total) {
        while (std::cin >> trans) {
			// if we're still processing the same book
            if (total.isbn() == trans.isbn()) 
                num++;
            else {          
                std::cout << total.isbn() << " has " << num << " records" << std::endl;    
                num = 1;
                total = trans;  // total now refers to the next book
            }
		}
        std::cout << total.isbn() << " has " << num << " records" << std::endl;     // print the last transaction
    } else {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }

    return 0;
}
