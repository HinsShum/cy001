# @file app/resource/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 16:08:11
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

# search c files
file(GLOB _CFILES "*.c")

# if you don't want compile some c files, add them to CFILESOUT
set(CFILESOUT "")
filter_out(CFILESOUT _CFILES _CFILES)

# add c files to glob variable
set(CFILES ${CFILES} ${_CFILES} PARENT_SCOPE)
# set current directory to the glob search path
set(INCDIRS ${INCDIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" PARENT_SCOPE)