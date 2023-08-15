cmake_minimum_required(VERSION 3.5)
project(bt_example)

set(CMAKE_CXX_STANDARD 17)

find_package(behaviortree_cpp REQUIRED)

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    if (_variableName MATCHES "behaviortree_cpp")
        message(STATUS "${_variableName}=${${_variableName}}")
    endif()
endforeach()

add_executable(bt_example main.cpp)
target_link_libraries(bt_example ${behaviortree_cpp_LIBRARIES})

