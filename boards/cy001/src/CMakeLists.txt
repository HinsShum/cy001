# @file boards/cy001/src/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 16:08:39
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

file(GLOB CFILES "*.c")
set(CFILES_SKIP "")
filter_out(CFILES_SKIP CFILES CFILES)
set(G_C_FILES ${G_C_FILES} ${CFILES} PARENT_SCOPE)
set(G_INC_VPATH ${G_INC_VPATH} ${CMAKE_CURRENT_SOURCE_DIR}/inc PARENT_SCOPE)