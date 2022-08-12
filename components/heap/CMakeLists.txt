# @file components/heap/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 15:58:12
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(HEAP_CONFIG_FILE_DIRECTORY "" CACHE STRING "Absolute path to the directory with heap_config.h")

if(HEAP_CONFIG_FILE_DIRECTORY AND NOT EXISTS ${HEAP_CONFIG_FILE_DIRECTORY}/heap_config.h)
    message(FATAL_ERROR " heap_config.h file not found in the directory specified (${HEAP_CONFIG_FILE_DIRECTORY})\n"
        " Please specify absolute path to it from top-level CMake file:\n"
        "  set(HEAP_CONFIG_FILE_DIRECTORY <absolute path to heap_config.h directory> CACHE STRING \"\")\n"
        " or from CMake command line option:\n"
        " -DHEAP_CONFIG_FILE_DIRECTORY='/absolute_path/to/heap_config.h/directort'")
endif()

set(TARGET_NAME heap)
set(TARGET_INC_VPATH ${CMAKE_CURRENT_SOURCE_DIR}/inc)
file(GLOB_RECURSE TARGET_C_FILES "*.c")

add_library(${TARGET_NAME} STATIC ${TARGET_C_FILES})
target_include_directories(${TARGET_NAME} PUBLIC ${TARGET_INC_VPATH} PRIVATE ${HEAP_CONFIG_FILE_DIRECTORY})