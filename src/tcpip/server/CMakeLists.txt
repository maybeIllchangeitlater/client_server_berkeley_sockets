cmake_minimum_required(VERSION 3.25)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(tcp_server_run
        server_main.cpp
        ../common/socket.cpp
        ../common/socket.h
        acceptor.cpp
        acceptor.h
        server.cpp
        server.h
        ../../common/timestamper.h
        ../../common/thread_safe_que.h)

set_target_properties(tcp_server_run PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../..
        )
