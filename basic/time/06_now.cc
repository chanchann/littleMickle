/*
 * @Author: Shiyu Yi
 * @Github: https://github.com/chanchann
 */
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
std::string time_duration() {
    auto duration_hour = std::chrono::hours(1);
    auto duration_sec = std::chrono::duration_cast<std::chrono::seconds>(duration_hour);
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_hour);
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration_hour);

    std::string string;
    string += std::to_string(duration_hour.count()) + " hour = ";
    string += std::to_string(duration_sec.count()) + " seconds = ";
    string += std::to_string(duration_ms.count()) + " milliseconds = ";
    string += std::to_string(duration_us.count()) + " microseconds";
    return string;
}

int64_t time_stamp() {
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
    std::chrono::system_clock::duration duration = time_point.time_since_epoch();
    int64_t timestamp = duration.count();
    return timestamp;
}

std::string time_string() {
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm* tm = std::localtime(&time_t);

    std::stringstream stream;
    stream << std::put_time(tm, "%Y-%m-%d %X");
    return stream.str();
}

std::string time_stamp_formatted() {
    std::string date_time = time_string();
    std::string microseconds = std::to_string((time_stamp() / 1000) % 1000000);
    return date_time + "." + microseconds;
}

int main() {
    std::cout << time_duration() << '\n';
    std::cout << time_stamp() << '\n';
    std::cout << time_string() << '\n';
    std::cout << time_stamp_formatted() << '\n';
    return 0;
}