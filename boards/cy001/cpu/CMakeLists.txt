# @file boards/cy001/cpu/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 16:09:10
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

# search c files
file(GLOB CFILES "*.c")
file(GLOB ASMFILES "${CMAKE_CURRENT_SOURCE_DIR}/gcc/*.s")

# if you don't want compile some c files, add them to CFILESOUT
set(CFILESOUT "")
filter_out(CFILESOUT CFILES CFILES)

# add c files to glob variable
set(C_SOURCE_FILES ${C_SOURCE_FILES} ${CFILES} ${ASMFILES} PARENT_SCOPE)
# set current directory to the glob search path
set(G_SOURCE_INCLUDE_DIRS ${G_SOURCE_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" PARENT_SCOPE)