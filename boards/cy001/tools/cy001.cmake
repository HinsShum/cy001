# @file boards/cy001/tools/cy001.cmake
# @author HinsShum hinsshum@qq.com
# @date 2022/01/28 15:31:47
# @encoding utf-8
# @brief Here's the first line of every cy001.cmake,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(G_INC_VPATH ${G_INC_VPATH} ${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME})

add_definitions(-DCONFIG_OPTIONS_FILE="config/options.h")
add_definitions(-DCONFIG_HEAP_FILE="config/heap_config.h")

include(${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME}/config/cfg.cmake)

add_subdirectory(arch/stm32f10x)
add_subdirectory(boards/${BOARD_NAME}/cpu)
add_subdirectory(boards/${BOARD_NAME}/bsp)
add_subdirectory(boards/${BOARD_NAME}/src)
add_subdirectory(lib/st/stm32f10x/peripherals)