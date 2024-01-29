cmake_minimum_required(VERSION 3.25)
project(udp_server)

set(CMAKE_CXX_STANDARD 11)

add_executable(udp_server_run
        ../common/socket.cpp
        ../common/socket.h
        server.cpp
        server.h
        server_main.cpp
        ../../common/timestamper.h
        ../../common/thread_safe_que.h)

set_target_properties(udp_server_run PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../..
        )