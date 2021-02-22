#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
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

    std::unique_ptr<Statement> stmt(con->createStatement());
    if (!stmt) {
        std::cout << "stmt error" << std::endl;
        return -1;
    }
	// 执行各种SQL语句
    // To run simple queries, you can use the sql::Statement::execute(), sql::Statement::executeQuery(), and sql::Statement::executeUpdate() method
    // Use the method sql::Statement::execute() if your query does not return a result set or if your query returns more than one result set. 
    // stmt->execute("CREATE DATABASE test");
    stmt->execute("USE test");                                   // 选择数据库
    stmt->execute("DROP TABLE IF EXISTS test");                  // 如果表已存在，则删除
    stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");   // 创建表
    stmt->execute("INSERT INTO test(id, label) VALUES(1, 'a')"); //插入数据
}