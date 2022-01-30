/**
 * @file boards\cy001\src\main.c
 *
 * Copyright (C) 2022
 *
 * main.c is free software: you can redistribute it and/or modify
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
#include "cpu.h"
#include "plat.h"
#include "options.h"
#include "resource_pool.h"
#include "key_processing.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
int main(void)
{
    cpu_config();
    plat_init();
    for(;;) {
        __delay_ms(10);
        key_processing(resource_pool_get_key_careful("keyup"));
        key_processing(resource_pool_get_key_careful("key0"));
        key_processing(resource_pool_get_key_careful("key1"));
        key_processing(resource_pool_get_key_careful("key2"));
    }
}
