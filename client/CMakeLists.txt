cmake_minimum_required(VERSION 2.7)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client main.cpp frontend.cpp backend.cpp ${COMMON_SOURCE})