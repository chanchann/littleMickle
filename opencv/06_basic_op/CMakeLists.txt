cmake_minimum_required(VERSION 2.8)
project( DisplayImage CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( init init.cc )
target_link_libraries( init ${OpenCV_LIBS} )

add_executable( binOp binOp.cc )
target_link_libraries( binOp ${OpenCV_LIBS} )

add_executable( erode erode.cc )
target_link_libraries( erode ${OpenCV_LIBS} )

add_executable( blur blur.cc )
target_link_libraries( blur ${OpenCV_LIBS} )

add_executable( canny canny.cc )
target_link_libraries( canny ${OpenCV_LIBS} )

add_executable( traverse traverse.cc )
target_link_libraries( traverse ${OpenCV_LIBS} )

add_executable( equalizeHist equalizeHist.cc )
target_link_libraries( equalizeHist ${OpenCV_LIBS} )


