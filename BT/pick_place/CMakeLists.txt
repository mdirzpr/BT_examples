# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(example1)

set(CMAKE_CXX_STANDARD 17)

find_package(behaviortree_cpp REQUIRED)

add_executable(pickPlace main.cpp)
target_link_libraries(pickPlace BT::behaviortree_cpp)