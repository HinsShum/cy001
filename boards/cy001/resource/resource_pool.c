/**
 * @file boards\cy001\resource\resource_pool.c
 *
 * Copyright (C) 2022
 *
 * resource_pool.c is free software: you can redistribute it and/or modify
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
#include "resource_manager.h"
#include "device.h"
#include "driver.h"
#include "options.h"

/*---------- macro ----------*/
#define IMPORT_DEVICE(name)                                             \
        do {                                                            \
            void *dev = device_open(#name);                             \
            assert(dev);                                                \
            if(dev) {                                                   \
                __dev->add_resource(__dev, #name, dev);                 \
            }                                                           \
        } while(0)                                                      \

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static resource_manager_base_t __dev;

/*---------- function ----------*/
static void _resource_add(void)
{
    /* import devices */
    driver_search_device();
    IMPORT_DEVICE(com);
    IMPORT_DEVICE(flash1);
    IMPORT_DEVICE(flash2);
    IMPORT_DEVICE(wdt);
}

void resource_pool_init(void)
{
    /* create resource pool */
    if(__dev) {
        resource_manager_destroy(__dev);
    }
    __dev = resource_manager_create();
    /* add all resource */
    _resource_add();
}

void resource_pool_deinit(void)
{
    resource_manager_destroy(__dev);
    __dev = NULL;
}

void *resource_pool_get_device(const char *name)
{
    void *resource = NULL;

    if(__dev) {
        resource = __dev->get_resource(__dev, name);
    }

    return resource;
}
