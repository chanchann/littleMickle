cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( boxFilter boxFilter.cc )
target_link_libraries( boxFilter ${OpenCV_LIBS} )

add_executable( mean_filter mean_filter.cc )
target_link_libraries( mean_filter ${OpenCV_LIBS} )

add_executable( guassion guassion.cc )
target_link_libraries( guassion ${OpenCV_LIBS} )

add_executable( medianBlur medianBlur.cc )
target_link_libraries( medianBlur ${OpenCV_LIBS} )

add_executable( bilateralFilter bilateralFilter.cc )
target_link_libraries( bilateralFilter ${OpenCV_LIBS} )

