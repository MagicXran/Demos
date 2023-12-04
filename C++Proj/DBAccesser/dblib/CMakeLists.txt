cmake_minimum_required(VERSION 3.26)
project(dblib)

set(CMAKE_CXX_STANDARD 20)
set(LIB_NAME ociliba)

message(" CMAKE_CURRENT_SOURCE_DIR :" ${CMAKE_CURRENT_SOURCE_DIR})

# 设置默认的构建类型为 Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# 添加源文件
add_library(dblib SHARED  ${SRC_LIST})


# 添加 Debug 模式下的头文件和库
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(INC_PATH ${CMAKE_SOURCE_DIR}/include)
    set(LIB_PATH ${CMAKE_SOURCE_DIR}/debug/lib)

endif ()

# 添加 Release 模式下的头文件和库
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(INC_PATH ${CMAKE_SOURCE_DIR}/include)
    set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
endif ()

message(" CMAKE_BUILD_TYPE :" ${CMAKE_BUILD_TYPE})
message(" INC_PATH :" ${INC_PATH})
message(" LIB_PATH :" ${LIB_PATH})


target_include_directories(dblib PRIVATE ${INC_PATH})
target_link_directories(dblib PRIVATE ${LIB_PATH})
target_link_libraries(dblib PRIVATE ${LIB_NAME})


