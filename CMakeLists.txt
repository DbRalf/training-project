cmake_minimum_required(VERSION 3.10)
project(test_code LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(udp_socket src/udp_socket.cpp)
target_include_directories(udp_socket PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(keyboard_input src/keyboard_input.cpp)
target_include_directories(keyboard_input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(udp_messages src/udp_messages.cpp)
target_include_directories(udp_messages PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE udp_messages keyboard_input udp_socket)

add_executable(server_test src/server.cpp)
target_link_libraries(server_test PRIVATE udp_socket udp_messages keyboard_input)

add_executable(client_test src/client.cpp)
target_link_libraries(client_test PRIVATE udp_socket udp_messages keyboard_input)

