# @file lib/st/stm32f10x/peripheral/Src/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2021/11/22 16:32:29
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(TARGET_NAME "stlib")
set(G_LIBS ${G_LIBS} ${TARGET_NAME} PARENT_SCOPE)
set(TARGET_INC_VPATH ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(TARGET_C_FILES)

# set compile files
if(DEFINED HAL_ADC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_adc.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_adc_ex.c)
endif()

if(DEFINED HAL_CAN)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_can.c)
endif()

if(DEFINED HAL_CEC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_cec.c)
endif()

if(DEFINED HAL_CORTEX)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_cortex.c)
endif()

if(DEFINED HAL_CRC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_crc.c)
endif()

if(DEFINED HAL_DAC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_dac.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_dac_ex.c)
endif()

if(DEFINED HAL_DMA)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_dma.c)
endif()

if(DEFINED HAL_ETH)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_eth.c)
endif()

if(DEFINED HAL_EXTI)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_exti.c)
endif()

if(DEFINED HAL_FLASH)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_flash.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_flash_ex.c)
endif()

if(DEFINED HAL_GPIO)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_gpio.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_gpio_ex.c)
endif()

if(DEFINED HAL_HCD)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_hcd.c)
endif()

if(DEFINED HAL_I2C)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_i2c.c)
endif()

if(DEFINED HAL_I2S)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_i2s.c)
endif()

if(DEFINED HAL_IRDA)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_irda.c)
endif()

if(DEFINED HAL_IWDG)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_iwdg.c)
endif()

if(DEFINED HAL_MMC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_mmc.c)
endif()

if(DEFINED HAL_MSP)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_msp_template.c)
endif()

if(DEFINED HAL_NAND)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_nand.c)
endif()

if(DEFINED HAL_NOR)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_nor.c)
endif()

if(DEFINED HAL_PCCARD)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pccard.c)
endif()

if(DEFINED HAL_PCD)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pcd.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pcd_ex.c)
endif()

if(DEFINED HAL_PWR)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pwr.c)
endif()

if(DEFINED HAL_RCC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_rcc.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_rcc_ex.c)
endif()

if(DEFINED HAL_RTC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_rtc.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_rtc_ex.c)
endif()

if(DEFINED HAL_SD)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_sd.c)
endif()

if(DEFINED HAL_SMARTCARD)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_smartcard.c)
endif()

if(DEFINED HAL_SPI)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_spi.c)
endif()

if(DEFINED HAL_SRAM)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_sram.c)
endif()

if(DEFINED HAL_TIME)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_tim.c)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_tim_ex.c)
endif()

if(DEFINED HAL_TIMEBASE_RTC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_timebase_rtc_alarm_template.c)
endif()

if(DEFINED HAL_TIMEBASE_TIM)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_timbase_tim_template.c)
endif()

if(DEFINED HAL_UART)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_uart.c)
endif()

if(DEFINED HAL_USART)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_usart.c)
endif()

if(DEFINED HAL_WWDG)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_wwdg.c)
endif()

if(DEFINED HAL)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal.c)
endif()

if(DEFINED LL_ADC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_adc.c)
endif()

if(DEFINED LL_CRC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_crc.c)
endif()

if(DEFINED LL_DAC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_dac.c)
endif()

if(DEFINED LL_DMA)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_dma.c)
endif()

if(DEFINED LL_EXTI)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_exti.c)
endif()

if(DEFINED LL_FSMC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_fsmc.c)
endif()

if(DEFINED LL_GPIO)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_gpio.c)
endif()

if(DEFINED LL_I2C)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_i2c.c)
endif()

if(DEFINED LL_PWR)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_pwr.c)
endif()

if(DEFINED LL_RCC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_rcc.c)
endif()

if(DEFINED LL_RTC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_rtc.c)
endif()

if(DEFINED LL_SDMMC)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_sdmmc.c)
endif()

if(DEFINED LL_SPI)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_spi.c)
endif()

if(DEFINED LL_TIME)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_tim.c)
endif()

if(DEFINED LL_USART)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_usart.c)
endif()

if(DEFINED LL_USB)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_usb.c)
endif()

if(DEFINED LL_UTILS)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_utils.c)
endif()

add_library(${TARGET_NAME} STATIC ${TARGET_C_FILES})
target_include_directories(${TARGET_NAME} PUBLIC ${TARGET_INC_VPATH} PRIVATE ${G_INC_VPATH})