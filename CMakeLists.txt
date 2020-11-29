cmake_minimum_required(VERSION 3.17)
project(project)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(test main.cpp helper.cpp)
target_link_libraries(test ${OpenCV_LIBS})
