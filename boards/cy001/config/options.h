/**
 * @file boards\cy001\config\options.h
 *
 * Copyright (C) 2022
 *
 * options.h is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author HinsShum hinsshum@qq.com
 *
 * @encoding utf-8
 */
#ifndef __CY001_OPTIONS_H
#define __CY001_OPTIONS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "misc.h"
#include "version.h"
#include "heap.h"
#include "xlog.h"
#include "stm32f1xx.h"
#include "stm32f1xx_ll_conf.h"

/*---------- macro ----------*/
#ifdef NDEBUG
#define CONFIG_SILENCE
#endif

/* system variables defined
 */
#define SYS_VERSION                     ((VERSION_MAJOR << 24) | (VERSION_MINOR << 16) | (VERSION_FIX << 8) | VERSION_BUILD)
#define SYS_VERSION_STRING              (STRING(VERSION_MAJOR)"."STRING(VERSION_MINOR)"."STRING(VERSION_FIX)"."STRING(VERSION_BUILD))
#define SYS_MODEL_NAME                  ("CY001")
#define SYS_HW_VERSION                  ((HW_VERSION_MAJOR << 8) | HW_VERSION_MINOR)
#define SYS_PRODUCT_TIME                (__DATE__)
#define SYS_VENDOR                      "HinsShum"

/* system delay function
 */
#define __delay_ms(ms)                  mdelay(ms)
#define __delay_us(us)                  udelay(us)
#define __get_ticks()                   tick_get()
#define __get_ticks_from_isr()          tick_get()
#define __ms2ticks(ms)                  (ms)
#define __ticks2ms(ticks)               (ticks)

/* system critical functions
 */
#define __enter_critical()              enter_critical()
#define __exit_critical()               exit_critical()

/* system heap functions
 */
#define __malloc(size)                  heap_malloc(size)
#define __free(ptr)                     heap_free(ptr)
#define __heap_free_size_get()          heap_get_free_remaining_size()

/* log interface
 */
#if 0
#ifndef CONFIG_SILENCE
#include <stdio.h>
#define xlog_error(x, y...)             printf(COLOR_RED x, ##y)
#define xlog_warn(x, y...)              printf(COLOR_YELLOW x, ##y)
#define xlog_message(x, y...)           printf(COLOR_GREEN x, ##y)
#define xlog_info(x, y...)              printf(COLOR_WHITE x, ##y)
#define xlog_cont(x, y...)              printf(x, ##y)
#define xlog_tag_error(tag, x, y...)    printf("(" tag ")" x, ##y)
#define xlog_tag_warn(tag, x, y...)     printf("(" tag ")" x, ##y)
#define xlog_tag_message(tag, x, y...)  printf("(" tag ")" x, ##y)
#define xlog_tag_info(tag, x, y...)     printf("(" tag ")" x, ##y)
#else
#define xlog_error(x, y...)
#define xlog_warn(x, y...)
#define xlog_message(x, y...)
#define xlog_info(x, y...)
#define xlog_cont(x, y...)
#define xlog_tag_error(tag, x, y...)
#define xlog_tag_warn(tag, x, y...)
#define xlog_tag_message(tag, x, y...)
#define xlog_tag_info(tag, x, y...)
#endif
#endif

/* embed flash information
 */
#define CONFIG_EMBED_FLASH_BASE         (FLASH_BASE)
#define CONFIG_EMBED_FLASH_SIZE         (0x80000)       /*<< 512 * 1024 */
#define CONFIG_EMBED_FLASH_BLOCK_SIZE   (0x800)         /*<< 2 * 1024 */
#define CONFIG_EMBED_FLASH_END          (CONFIG_EMBED_FLASH_BASE + CONFIG_EMBED_FLASH_SIZE)
#define CONFIG_EMBED_FLASH_WRITE_GRAN   (32)

/* w25qxx information
 */
#define CONFIG_W25Q64_BASE              (0x00)
#define CONFIG_W25Q64_SIZE              (0x800000)
#define CONFIG_W25Q64_BLOCK_SIZE        (0x1000)
#define CONFIG_W25Q64_END               (CONFIG_W25Q64_BASE + CONFIG_W25Q64_SIZE)
#define CONFIG_W25Q64_WRITE_GRAN        (32)

/* config interrupt priority
 * all bits for gourp priorities, no bit for sub priorities
 */
#define CONFIG_PRIORITY_MSK             ((1UL << __NVIC_PRIO_BITS) - 1UL)
#define CONFIG_PRIORITY_MAKE(prio)      (CONFIG_PRIORITY_MSK - (prio & CONFIG_PRIORITY_MSK))
#define CONFIG_PRIORITY_SYSTICK         NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CONFIG_PRIORITY_MAKE(0), 0)
#define CONFIG_PRIORITY_COM             NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CONFIG_PRIORITY_MAKE(1), 0)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void udelay(uint32_t us);
extern void mdelay(uint32_t delay);
extern uint64_t tick_get(void);
extern void enter_critical(void);
extern void exit_critical(void);

#ifdef __cplusplus
}
#endif
#endif /* __CY001_OPTIONS_H */
