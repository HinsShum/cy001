/**
 * @file app\resource\inc\resource_pool.h
 *
 * Copyright (C) 2022
 *
 * resource_pool.h is free software: you can redistribute it and/or modify
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
#ifndef __RESOURCE_POOL_H
#define __RESOURCE_POOL_H

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
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void resource_pool_init(void);
extern void resource_pool_deinit(void);
extern void *resource_pool_get_device(const char *name);
extern void *resource_pool_get_device_careful(const char *name);
extern void *resource_pool_get_key(const char *name);
extern void *resource_pool_get_key_careful(const char *name);

#ifdef __cplusplus
}
#endif
#endif /* __RESOURCE_POOL_H */
