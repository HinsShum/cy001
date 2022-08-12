# @file common/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 15:40:53
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

file(GLOB FILES "*.c")

# set filter out files
set(FILES_OUT "")
filter_out(FILES_OUT FILES FILES)

set(G_C_FILES ${G_C_FILES} ${FILES} PARENT_SCOPE)
set(G_INC_VPATH ${G_INC_VPATH} "${CMAKE_CURRENT_SOURCE_DIR}/inc" PARENT_SCOPE)