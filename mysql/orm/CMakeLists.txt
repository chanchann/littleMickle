CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(sqlpp)

SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic" )

ADD_EXECUTABLE(test
    test.cc
)
# target_link_libraries(test ${sqlpp11_LIBRARIES})
# target_link_libraries(test ${sqlpp11-connector-mysql_LIBRARIES})

target_link_libraries(test sqlpp-mysql mysqlclient)

# target_link_libraries(test ${sqlpp11_LIBRARIES} ${sqlpp11-connector-mysql_LIBRARIES})
