project(test_opencv)  
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
find_package(OpenCV REQUIRED)  
add_executable(test_opencv objectDetection.cpp)  
target_link_libraries(test_opencv ${OpenCV_LIBS})  
cmake_minimum_required(VERSION 2.8)
