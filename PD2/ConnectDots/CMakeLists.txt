cmake_minimum_required(VERSION 2.8)
project(connect)
find_package (OpenCV REQUIRED)
add_executable (connect connect.cpp)
target_link_libraries (connect ${OpenCV_LIBS})
