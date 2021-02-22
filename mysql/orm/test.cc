#include "TabSample.h"
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>
#include <iostream>

namespace mysql = sqlpp::mysql;

int main() {
	auto config = std::make_shared<mysql::connection_config>();
 	config->user = "root";
 	config->database = "test";
    config->password = "123";
	config->debug = true;
	mysql::connection db(config);

	TabSample tab;
	for(const auto& row : db.run(sqlpp::select(all_of(tab)).from(tab).unconditionally())) {
		std::cerr << "row.alpha: " << row.alpha << ", row.beta: " << row.beta << ", row.gamma: " << row.gamma <<  std::endl;
	};
    return 0;
}