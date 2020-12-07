cmake_minimum_required(VERSION 3.17)
project(project)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(PCSC_image_processing main.cpp helper.cpp)
target_link_libraries(PCSC_image_processing ${OpenCV_LIBS})
