/**
 * SQL语句返回的结果集
 * sql::Statement::executeQuery()和sql::PreparedStatement::executeQuery()返回
 * 
 */
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
    con->setSchema("test");
    std::unique_ptr<Statement> stmt(con->createStatement());
    if (!stmt) {
        std::cout << "stmt error" << std::endl;
        return -1;
    }
    std::unique_ptr<ResultSet> res(stmt->executeQuery("SELECT id, label FROM test ORDER BY id ASC"));
    while (res->next()) {
        // You can use either numeric offsets...
        std::cout << "id = " << res->getInt(1); // getInt(1) returns the first column
        // ... or column names for accessing results.
        // The latter is recommended.
        std::cout << ", label = '" << res->getString("label") << "'" << std::endl;
    }
}