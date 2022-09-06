/**
 * @file app/src/fputc.c
 *
 * Copyright (C) 2021
 *
 * fputc.c is free software: you can redistribute it and/or modify
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

/*---------- includes ----------*/
#include "serial.h"
#include "resource_pool.h"
#include "options.h"
#include <stdio.h>

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
static void *_serial;

/*---------- function ----------*/
#if defined(__ARMCC_VERSION)
#if !defined(__MICROLIB)
#if defined(__CC_ARM)
struct __FILE {
   int handle;
};
#endif
FILE __stdout;
#endif
int fputc(int ch, FILE *p)
{
    uint8_t c = (uint8_t)ch;

    if(_serial == NULL) {
        _serial = resource_pool_get_device_careful("com");
    }
    device_write(_serial, &c, SERIAL_WRITE_CHANGE_DIR_AUTOMATICALLY, sizeof(c));

    return ch;
}
#else
int _write(int fd, char *buf, int size)
{
    if(_serial == NULL) {
        _serial = resource_pool_get_device_careful("com");
    }
    device_write(_serial, (void *)buf, SERIAL_WRITE_CHANGE_DIR_AUTOMATICALLY, size);

    return size;
}
#endif
