/**
 * @file boards\cy001\src\plat.c
 *
 * Copyright (C) 2022
 *
 * plat.c is free software: you can redistribute it and/or modify
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
#include "plat.h"
#include "resource_pool.h"
#include "xlog.h"
#include "serial.h"
#include "errorno.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
static void _stdout(const char *str, uint32_t length)
{
    static void *device = NULL;

    if(!device) {
        device = resource_pool_get_device_careful("com");
    }
    device_write(device, (void *)str, SERIAL_WRITE_CHANGE_DIR_AUTOMATICALLY, length);
}

void plat_init(void)
{
    xlog_ops_t ops = {
        .print = _stdout
    };

    xlog_init(&ops);
    resource_pool_init();
}

void plat_deinit(void)
{
    resource_pool_deinit();
}
