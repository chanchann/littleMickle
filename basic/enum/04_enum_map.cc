/*
定义一个map，将enum映射到string

https://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
*/
#include <unordered_map>
#include <iostream>
enum class CarType {
    CITY_CAR, SPORTS_CAR, SUV
};

struct EnumClassHash {
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

std::unordered_map<CarType, std::string, EnumClassHash> mp {
    {CarType::CITY_CAR, "CITY_CAR"},
    {CarType::SPORTS_CAR, "SPORTS_CAR"},
    {CarType::SUV, "SUV"},
};

int main() {
    std::string test = mp[CarType::SUV];
    std::cout << test << std::endl;
    return 0;
}
