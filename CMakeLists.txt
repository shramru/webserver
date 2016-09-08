cmake_minimum_required(VERSION 3.6)
project(webserver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Boost 1.40.0 REQUIRED system)

include_directories(include)
set(SOURCE_FILES src/main.cpp src/threadpool.cpp src/threadpool.tcc src/server.cpp src/connection.cpp src/request_handler.cpp)

add_executable(webserver ${SOURCE_FILES})
target_link_libraries(webserver -lpthread ${Boost_LIBRARIES})