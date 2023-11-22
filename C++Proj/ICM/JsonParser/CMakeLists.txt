cmake_minimum_required(VERSION 3.25)

#add_library(JsonParse )



add_executable(TEST_JSON tesJson.cpp)
target_include_directories(TEST_JSON PRIVATE ${INC_DIR})
