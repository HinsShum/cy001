# @file utest/cpputest/common/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/02/07 13:10:18
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

file(GLOB CXXFILES "*.cpp")

set(CXXFILESOUT "")
filter_out(CXXFILESOUT CXXFILES CXXFILES)

set(G_CXX_FILES ${G_CXX_FILES} ${CXXFILES} PARENT_SCOPE)