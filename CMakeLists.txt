cmake_minimum_required(VERSION 3.24)
project(trial)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_BUILD_TYPE Debug)


include_directories(/usr/include/mysql)

add_executable(server server.cpp server.h main_server.cpp Thread.cpp Thread.h)
add_executable(client client.cpp client.h main_client.cpp)
add_executable(client1 client.cpp client.h main_client.cpp)

target_link_libraries(server pthread mysqlclient)