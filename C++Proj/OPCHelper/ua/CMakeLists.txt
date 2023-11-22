cmake_minimum_required(VERSION 3.26)

# 设置策略CMP0091为NEW，新策略
if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(ua)

#变量 BUILD_SHARED_LIBS 可以设置 add_library 库文件的生成类型，当值是 ON 时生成动态库，OFF 生成静态库。
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

#2. 查找源文件
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
message("SRC_LIST: " ${SRC_LIST})

#4. 指定输出目录:使用 LIBRARY_OUTPUT_PATH 参数可指定库文件的生成路径：
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#3. 添加源文件,add_library 中使用关键字 SHARED、STATIC 分别指定生成动态库、静态库文件
add_library(ua ${SRC_LIST}
        )


#连接第三方库
target_link_libraries(ua PRIVATE ws2_32 Iphlpapi)

#宏定义
target_compile_definitions(ua PRIVATE EXPORTS_UA_LIB)

#1. 包含头文件
target_include_directories(ua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
message('CMAKE_CURRENT_SOURCE_DIR' ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#5. 设置目标属性 /mtd
set_property(TARGET ua PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 可选：设置编译选项，例如编译标志、优化等
# target_compile_options(YourLibraryName PRIVATE -Wall -O2)

# 6. 构建
#cmake -B build -S .
#cmake --build ./build