// TEST

#include <unordered_map>
#include <iostream>
enum class CarType {
    CITY_CAR, SPORTS_CAR, SUV
};


std::unordered_map<CarType, std::string, std::hash<int> > mp {
    {CarType::CITY_CAR, "CITY_CAR"},
    {CarType::SPORTS_CAR, "SPORTS_CAR"},
    {CarType::SUV, "SUV"},
};

int main() {
    std::string test = mp[CarType::SUV];
    std::cout << test << std::endl;
    // mp.insert({CarType::SUV, "test"});
    // for(auto it = mp.begin(); it != mp.end(); it++) {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }
    
    return 0;
}
