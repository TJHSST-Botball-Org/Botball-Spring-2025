cmake_minimum_required(VERSION 3.3)
project( main )
add_executable( main src/main.cpp )
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS} PRIVATE include)

