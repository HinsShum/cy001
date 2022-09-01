# @file common/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 15:40:53
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.20)

set(C_FILES)
set(INC_VPATH)

file(GLOB_RECURSE SUBCMAKELISTS "CMakeLists.txt")
dirname(SUBCMAKELISTS SUBCMAKELISTS_DIRS)
filter_out(CMAKE_CURRENT_SOURCE_DIR SUBCMAKELISTS_DIRS SUBCMAKELISTS_DIRS)
foreach(SUBCMAKELISTS_DIR ${SUBCMAKELISTS_DIRS})
    add_subdirectory(${SUBCMAKELISTS_DIR})
endforeach(SUBCMAKELISTS_DIR)

set(G_C_FILES ${G_C_FILES} ${C_FILES} PARENT_SCOPE)
set(G_INC_VPATH ${G_INC_VPATH} ${INC_VPATH} PARENT_SCOPE)