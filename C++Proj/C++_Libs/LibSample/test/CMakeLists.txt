cmake_minimum_required(VERSION 3.26)

# 设置策略CMP0091为NEW，新策略
if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(test)

#指定库的生成类型
option(BUILD_SHARED_LIBS  "Build shared libraries" ON)

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

message('SRC_LIST' ${SRC_LIST})
message('CMAKE_CURRENT_SOURCE_DIR' ${CMAKE_CURRENT_SOURCE_DIR})
message('PROJECT_SOURCE_DIR' ${PROJECT_SOURCE_DIR})

#指定输出目录
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_library(test ${SRC_LIST})

# add micro
target_compile_definitions(test PRIVATE LOGLIB_EXPORTS)

target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set_property(TARGET test PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
