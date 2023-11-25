cmake_minimum_required(VERSION 3.26)
project(QtSlabTempCompared)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 自动调用moc，uic，rcc处理qt的扩展部分
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/mingw81_32) #这里需要填入自己安装的路径
#set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019")


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

set(INC_DIR ${PROJECT_SOURCE_DIR}/inc)
set(Dll_List SlabTempCalDll)
message("Dll_List:" ${Dll_List})
message("INC_DIR:" ${INC_DIR})
add_executable(QtSlabTempCompared main.cpp
        slabtempcomaredrender.cpp
        slabtempcomaredrender.h
        slabtempcomaredrender.ui
        temp_calc.cpp
)

target_include_directories(QtSlabTempCompared PRIVATE ${INC_DIR})

# 指定库文件所在目录
target_link_directories(QtSlabTempCompared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

target_link_libraries(QtSlabTempCompared
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
)

target_link_libraries(QtSlabTempCompared SlabTempCalDll)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        message("copy" "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll" "---->" ${TARGET_FILE_DIR}:${PROJECT_NAME}>)
    endforeach (QT_LIB)

    foreach (TDll ${Dll_List})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_SOURCE_DIR}/libs/${TDll}.dll"
                "${CMAKE_BINARY_DIR}")
        message("copy" "${CMAKE_SOURCE_DIR}/libs/${TDll}.dll"  "---->"  ${CMAKE_BINARY_DIR})
    endforeach (TDll)
endif ()
