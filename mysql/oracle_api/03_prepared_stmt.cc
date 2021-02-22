/**
 * Statement类执行的语句只能是静态的字符串
 * PreparedStatement类执行的语句可以含有变量（采用占位符思想实现）
 */

#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <memory>
using namespace sql;

int main() {
    mysql::MySQL_Driver *driver;

    driver = mysql::get_mysql_driver_instance();
    if (!driver) {
        std::cout << "dirver error" << std::endl;
        return -1;
    }

    std::unique_ptr<Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "123"));
    if (!con) {
        std::cout << "conn error" << std::endl;
        return -1;
    }
    /* Connect to the MySQL test database */
    con->setSchema("test");
    std::unique_ptr<PreparedStatement> pstmt(con->prepareStatement("INSERT INTO test(id, label) VALUES(?, ?)"));
    if (!pstmt) {
        std::cout << "prepared stmt error" << std::endl;
        return -1;
    }
    // 填充占位符
    pstmt->setInt(1, 10);  // 给第一个占位符填充数字10
    pstmt->setString(2, "b");  // 给第二个占位符填充字符串"b"
    pstmt->execute();

    pstmt->setInt(1, 12);
    pstmt->setString(2, "c");
    pstmt->execute();
}