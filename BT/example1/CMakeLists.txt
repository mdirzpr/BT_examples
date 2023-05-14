# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(example1)

set(CMAKE_CXX_STANDARD 17)

find_package(behaviortree_cpp REQUIRED)

add_executable(bt_example main.cpp)
target_link_libraries(bt_example BT::behaviortree_cpp)