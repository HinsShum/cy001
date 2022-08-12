# @file boards\cy001\config\components.cmake
# @author HinsShum hinsshum@qq.com
# @date 2022/08/13 13:28:49
# @encoding utf-8
# @brief Here's the first line of every components.cmake,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

# build in heap components
set(HEAP_CONFIG_FILE_DIRECTORY ${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME}/config/port CACHE STRING [FORCE])
set(HEAP_BUILDIN "y")