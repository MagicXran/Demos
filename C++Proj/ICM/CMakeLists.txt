cmake_minimum_required(VERSION 3.25)
project(ICM)

set(CMAKE_CXX_STANDARD 17)


set(INC_DIR  ${PROJECT_SOURCE_DIR}/inc)
message('INC_DIR' ${INC_DIR})
set(LIB_DIR ${PROJECT_SOURCE_DIR}/libs)
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

# 定义需要查找的库列表
set(LIBRARIES_TO_FIND
        MDWlib
        HWapi
        MdwSystem
        AlarmAPI
        TagApi
        SRmsg
        rdfmapi
        DataAccessor
        ociliba
        fmtd
        spdlogd
        vld

        # 添加其他库的名称到这里
)

set(LIBRARY_DIRS "C:/Program Files (x86)/NERCAR/PCDP/API"
        "C:/Program Files (x86)/NERCAR/PCDP/LIB"
        "C:/Program Files (x86)/NERCAR/PCDP/BIN"
)


#add_executable(MAIN main.cpp)

#add_subdirectory(JsonParser)
add_subdirectory(DBHelper)
#add_subdirectory(ERP)
add_subdirectory(test)