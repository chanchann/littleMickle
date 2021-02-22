CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(connect)

SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic" )

ADD_EXECUTABLE(connect
    01_connect.cc
)
target_link_libraries(connect mysqlcppconn)

ADD_EXECUTABLE(simple_query
    02_simple_query.cc
)
target_link_libraries(simple_query mysqlcppconn)

ADD_EXECUTABLE(prepared_stmt
    03_prepared_stmt.cc
)
target_link_libraries(prepared_stmt mysqlcppconn)

ADD_EXECUTABLE(result_set
    04_result_set.cc
)
target_link_libraries(result_set mysqlcppconn)
