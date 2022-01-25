/**
 * @file common\inc\soft_timer.h
 *
 * Copyright (C) 2022
 *
 * soft_timer.h is free software: you can redistribute it and/or modify
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
#ifndef __SOFT_TIMER_H
#define __SOFT_TIMER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
/*---------- type define ----------*/
enum {
    SOFTTIMER_MODE_SINGLE,
    SOFTTIMER_MODE_REPEAT
};

enum {
    SOFTTIMER_ERR_OK,
    SOFTTIMER_ERR_ERROR,
    SOFTTIMER_ERR_FULL,
    SOFTTIMER_ERR_NOT_FOUND,
    SOFTTIMER_ERR_EXIT
};

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void soft_timer_init(void);
extern void soft_timer_deinit(void);
extern int32_t soft_timer_create(const char *name, uint8_t mode, uint32_t period, void *cb_data, void (*cb)(void *cb_data));
extern int32_t soft_timer_destroy(const char *name);
extern void soft_timer_poll(void);
extern void soft_timer_tick(void);

#ifdef __cplusplus
}
#endif
#endif /* __SOFT_TIMER_H */
