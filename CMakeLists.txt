cmake_minimum_required(VERSION 3.15)
project(simple_chat)

include_directories(common)
set(COMMON_SOURCE ${PROJECT_SOURCE_DIR}/common/chat_protocol.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(client)
add_subdirectory(server)
