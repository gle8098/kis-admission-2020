cmake_minimum_required(VERSION 3.15)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp chat_logic.cpp client_session.cpp server.cpp ${COMMON_SOURCE})