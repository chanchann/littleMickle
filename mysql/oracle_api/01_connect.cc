#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <memory>

using namespace sql;

int main() {
    mysql::MySQL_Driver *driver;
    // is not thread-safe. 
    // 加载驱动是每个mysql接口编程的基础
    driver = mysql::get_mysql_driver_instance();
    if (driver) {
        std::cout << "dirver ok" << std::endl;
    }
    // sql::Connection::isValid() checks whether the connection is alive
    // sql::Connection::reconnect() reconnects if the connection has gone down
    std::unique_ptr<Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "123"));
    if (con) {
        std::cout << "conn ok" << std::endl;
    }
	// driver不需要显式delete，Connection对象会小心释放它
}