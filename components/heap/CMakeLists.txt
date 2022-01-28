# @file components/heap/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 15:58:12
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

# search c files
file(GLOB CFILES "*.c")

# if you don't want compile some c files, add them to CFILESOUT
set(CFILESOUT "")
filter_out(CFILESOUT CFILES CFILES)

# add c files to target variable
set(TARGET_CFILES ${TARGET_CFILES} ${CFILES} PARENT_SCOPE)
# set current directory to the glob search path
set(TARGET_INC_DIRS ${TARGET_INC_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" PARENT_SCOPE)