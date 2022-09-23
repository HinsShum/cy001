/**
 * @file utest/cpputest/config/options.h
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
#ifndef __UTEST_OPTIONS_H
#define __UTEST_OPTIONS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

/*---------- macro ----------*/
#ifdef NDEBUG
#define CONFIG_SILENCE
#endif

/* system delay function
 */
#define __delay_ms(ms)
#define __delay_us(us)
#define __get_ticks()                   (0)
#define MS2TICKS(ms)                    (ms)
#define TICKS2MS(ticks)                 (ticks)

/* system critical functions
 */
#define __enter_critical()
#define __exit_critical()

/* system heap functions
 */
#define __malloc(size)                  malloc(size)
#define __free(ptr)                     free(ptr)

/* print macros
 */
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

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/

#ifdef __cplusplus
}
#endif
#endif /* __UTEST_OPTIONS_H */
