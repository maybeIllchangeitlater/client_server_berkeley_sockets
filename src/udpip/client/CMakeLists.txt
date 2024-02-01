cmake_minimum_required(VERSION 3.25)
project(udp_server)

set(CMAKE_CXX_STANDARD 11)

add_executable(udp_client_run
        ../common/socket.cpp
        ../common/socket.h
        client.cpp
        client.h
        client_main.cpp)

set_target_properties(udp_client_run PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../..
        )