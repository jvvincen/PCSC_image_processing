cmake_minimum_required(VERSION 3.16)
project(project)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(test main.cpp helper.cpp ImageClass.cpp)
target_link_libraries(test ${OpenCV_LIBS})
