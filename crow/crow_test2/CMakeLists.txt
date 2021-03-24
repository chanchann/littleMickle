CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(corw)

SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread" )

set(CMAKE_BUILD_TYPE "Debug")

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(server main.cc)

target_link_libraries(server 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)