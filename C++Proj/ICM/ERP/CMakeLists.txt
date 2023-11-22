cmake_minimum_required(VERSION 3.25)
project(ERP)
#set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${INC_DIR}/*.cpp")
message('SRC_LIST' ${SRC_LIST})

#file(GLOB INC_DIR
#        "${PROJECT_SOURCE_DIR}/inc/*.h"
#        "${PROJECT_SOURCE_DIR}/inc/*.hpp"
#)


add_executable(ERP ${SRC_LIST})
target_compile_definitions(ERP PRIVATE _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS ENABLE_DEBUG)

target_include_directories(ERP PRIVATE ${INC_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${LIBRARY_DIRS})
message('CMAKE_CURRENT_SOURCE_DIR' ${CMAKE_CURRENT_SOURCE_DIR})

# 链接到含有库文件的目录 .lib
target_link_directories(ERP PRIVATE
        ${LIBRARY_DIRS}
        ${LIB_DIR}
)


target_link_libraries(ERP PRIVATE ${LIBRARIES_TO_FIND})