#include <iostream>
#include "Sales_item.h"

int main()  {
    Sales_item total, trans; 

    std::cout << "Please enter some same isbn trans record : " << std::endl;
    if (std::cin >> total) {
        while (std::cin >> trans) {
			// if we're still processing the same book
            if (compareIsbn(total, trans)) {
                total += trans; // update the running total 
            } else {              
                std::cout << "ISBN is not the same" << std::endl;
                return -1;
            }
		}
        std::cout << "Total : " << total << std::endl; // print the last transaction
    } else {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
    return 0;
}
