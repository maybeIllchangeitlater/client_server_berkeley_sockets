cmake_minimum_required(VERSION 3.25)
project(client)

set(CMAKE_CXX_STANDARD 11)

add_executable(client_run
        client_main.cpp
        ../common/socket.cpp
        ../common/socket.h
        client.cpp
        client.h)

set_target_properties(client_run PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../..
        )
