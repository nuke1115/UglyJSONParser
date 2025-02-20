###### project settings
cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME UglyJSONParser)

project(
    ${LIBRARY_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#######################
###### set variables
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/output)
set(
    SRC_FILES
    ${SRC_DIR}/FileIO/FileIOManager.cpp
    ${SRC_DIR}/JSONParser/JSONParser.cpp
    ${SRC_DIR}/JSONTree/JSONTreeBuilder.cpp
    ${SRC_DIR}/JSONTree/Node.cpp
    ${SRC_DIR}/JSONTree/NodeBase.cpp
    ${SRC_DIR}/Tokenizer/Tokenizer.cpp
    ${SRC_DIR}/Utils/StringUtils.cpp
    ${SRC_DIR}/Utils/TypeUtils.cpp
)
####################
####### set library
add_library(
    ${LIBRARY_NAME}
    STATIC
    ${SRC_FILES}
)

set_target_properties(
    ${LIBRARY_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
###################