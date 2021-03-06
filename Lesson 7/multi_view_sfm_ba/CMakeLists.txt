cmake_minimum_required(VERSION 2.8 FATAL_ERROR)  
  
project(cloud_viewer)  
  
find_package(PCL 1.7.2 REQUIRED)  
find_package(OpenCV REQUIRED)
SET(CMAKE_C_COMPILER g++)
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)

set(INC_LOCAL_DIR  /usr/local/include/ /root/SSBA/ ${cloud_viewer_SOURCE_DIR} ${PCL_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})  
set(LINK_DIR /usr/local/lib /usr/lib/x86_64-linux-gnu /root/SSBA/build ${PCL_LIBRARY_DIRS})
AUX_SOURCE_DIRECTORY(${cloud_viewer_SOURCE_DIR} SOURCE_FILES)
set(MYDEPENDS boost_filesystem boost_system)
include_directories(${INC_LOCAL_DIR}) 
link_directories(${LINK_DIR})  
add_definitions(${PCL_DEFINITIONS})  
add_executable (cloud_viewer ${SOURCE_FILES})  
target_link_libraries (cloud_viewer ${PCL_LIBRARIES} ${OpenCV_LIBS} ${MYDEPENDS} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} V3D colamd) 