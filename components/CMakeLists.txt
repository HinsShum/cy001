# @file components/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 15:52:01
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

if(DEFINED HEAP_BUILDIN)
add_subdirectory(heap)
set(G_LIBS ${G_LIBS} heap PARENT_SCOPE)
endif()