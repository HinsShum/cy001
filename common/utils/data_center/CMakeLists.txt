# @file common\utils\data_center\CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/09/01 14:47:16
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.20)

file(GLOB _C_FILES "*.c")
set(_C_FILES_SKIP "")
filter_out(_C_FILES_SKIP _C_FILES _C_FILES)
set(C_FILES ${C_FILES} ${_C_FILES} PARENT_SCOPE)
set(INC_VPATH ${INC_VPATH} ${CMAKE_CURRENT_SOURCE_DIR}/inc PARENT_SCOPE)