# @file utest/cpputest/tools/utest.cmake
# @author HinsShum hinsshum@qq.com
# @date 2022/02/07 12:29:03
# @encoding utf-8
# @brief Here's the first line of every utest.cmake,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(TOP_DIRS "${PROJECT_SOURCE_DIR}/../..")

# close print log
add_definitions(-DNDEBUG)
add_definitions(-DCONFIG_OPTIONS_FILE="config/options.h")

# add cpputest library
set(G_LIBS ${G_LIBS} "CppUTest" "CppUTestExt" "pthread")

# add source files
set(G_C_FILES ${G_C_FILES} "${TOP_DIRS}/common/soft_timer.c")
set(G_INC_VPATH ${G_INC_VPATH} "${TOP_DIRS}/common/inc")

# add sub directory
add_subdirectory(common)