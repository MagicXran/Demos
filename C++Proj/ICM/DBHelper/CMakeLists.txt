cmake_minimum_required(VERSION 3.25)
project(TEST_DB)

message(${CMAKE_CURRENT_BINARY_DIR})

set(OCILIB  ociliba)
set(OCIDIR  "C:/Projects/ICM/inc/ocilib"   "C:/Projects/ICM/bin"  "C:/Projects/ICM/libs")

#set_target_properties(TEST_DB  PROPERTIES IMPORTED_LOCATION  "C:/Projects/ICM/bin/${OCILIB}.dll")
#message("set-----------" "C:/Projects/ICM/bin/${OCILIB}.dll")


add_executable(TEST_DB DBHelper.cpp main.cpp)



# 循环遍历库列表，依次查找每个库
foreach(LIBRARY ${OCILIB})
    find_library(${LIBRARY}_LIBRARY
            NAMES ${LIBRARY}
            PATHS ${OCIDIR}
            )

    # 输出找到的库文件路径（可选）
    message(STATUS "找到库文件: " ${${LIBRARY}_LIBRARY})

    target_include_directories(TEST_DB PUBLIC  ${OCIDIR})
    target_link_libraries(TEST_DB PUBLIC ${${LIBRARY}_LIBRARY})
endforeach()

