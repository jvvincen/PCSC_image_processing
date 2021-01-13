cmake_minimum_required(VERSION 3.17)
project(test)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(Projet_PCSC_final main.cpp helper.cpp helper.h image.cpp image.h fourier.cpp fourier.h filter.cpp filter.h)
target_link_libraries(Projet_PCSC_final ${OpenCV_LIBS})