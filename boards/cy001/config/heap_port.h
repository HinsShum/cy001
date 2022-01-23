/**
 * @file boards\cy001\config\heap_port.h
 *
 * Copyright (C) 2022
 *
 * heap_port.h is free software: you can redistribute it and/or modify
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
#ifndef __HEAP_PORT_H
#define __HEAP_PORT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
#define PORT_TOTAL_HEAP_SIZE                       ((size_t)30 * 1024)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/

#ifdef __cplusplus
}
#endif
#endif /* __HEAP_PORT_H */