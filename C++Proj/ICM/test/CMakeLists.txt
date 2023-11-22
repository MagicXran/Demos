cmake_minimum_required(VERSION 3.25)
project(TEST)

set(CMAKE_C_STANDARD 17)


file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

message('SRC_LIST: ' ${SRC_LIST})
add_executable(TEST  ${SRC_LIST}
        )