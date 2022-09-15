# @file boards\cy001\config\cfg.cmake
# @author HinsShum hinsshum@qq.com
# @date 2022/09/15 09:42:25
# @encoding utf-8
# @brief Here's the first line of every cfg.cmake,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.20)

# library configure
set(HAL_CORTEX, "y")
set(HAL_FLASH "y")
set(LL_GPIO "y")
set(LL_RCC "y")
set(LL_SPI "y")
set(LL_USART "y")
set(LL_UTILS "y")

# driver configure
set(FLASH "y")
set(FM25QXX "y")
set(SERIAL "y")
set(WDT "y")
set(GPIO "y")