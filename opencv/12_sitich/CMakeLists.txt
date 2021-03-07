cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( surf surf.cc )
target_link_libraries( surf ${OpenCV_LIBS} )

add_executable( test test.cc )
target_link_libraries( test ${OpenCV_LIBS} )

# add_executable( test2 test2.cc )
# target_link_libraries( test2 ${OpenCV_LIBS} )

add_executable( test3 test3.cc )
target_link_libraries( test3 ${OpenCV_LIBS} )
