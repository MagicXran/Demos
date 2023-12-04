cmake_minimum_required(VERSION 3.26)
project(DBAccesser)

set(CMAKE_CXX_STANDARD 20)

#message(" CMAKE_CURRENT_SOURCE_DIR :" ${CMAKE_CURRENT_SOURCE_DIR})
#file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#message(" SRC_LIST :" ${SRC_LIST})


add_subdirectory(dblib)

#add_executable(DBAccesser ${SRC_LIST})
#target_include_directories(DBAccesser PRIVATE "X:/Demos/C++Proj/DBAccesser/dblib/ocilib/include")
#target_link_directories(DBAccesser PRIVATE "X:/Demos/C++Proj/DBAccesser/dblib/ocilib/debug/lib")
#target_link_libraries(DBAccesser PRIVATE ociliba)
