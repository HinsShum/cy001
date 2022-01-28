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
#define IMPORT_DEVICE(name, pool)                                       \
        do {                                                            \
            void *dev = device_open(#name);                             \
            assert(dev);                                                \
            if(dev) {                                                   \
                pool->add_resource(pool, #name, dev);                   \
            }                                                           \
        } while(0)

#define EXPORT_DEVICE(name, pool)                                       \
        do {                                                            \
            void *dev = pool->get_resource(pool, #name);                \
            assert(dev);                                                \
            if(dev) {                                                   \
                device_close(dev);                                      \
                pool->remove_resource(pool, #name);                     \
            }                                                           \
        } while(0)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static resource_manager_base_t devices_pool;

/*---------- function ----------*/
static void _resource_add(void)
{
    /* import devices */
    driver_search_device();
    IMPORT_DEVICE(com, devices_pool);
    IMPORT_DEVICE(flash1, devices_pool);
    IMPORT_DEVICE(flash2, devices_pool);
    IMPORT_DEVICE(wdt, devices_pool);
}

static void _resource_remove(void)
{
    /* export devices */
    EXPORT_DEVICE(com, devices_pool);
    EXPORT_DEVICE(flash1, devices_pool);
    EXPORT_DEVICE(flash2, devices_pool);
    EXPORT_DEVICE(wdt, devices_pool);
}

void resource_pool_init(void)
{
    /* create resource pool */
    if(devices_pool) {
        resource_manager_destroy(devices_pool);
    }
    devices_pool = resource_manager_create();
    /* add all resource */
    _resource_add();
}

void resource_pool_deinit(void)
{
    /* remove all resource */
    _resource_remove();
    resource_manager_destroy(devices_pool);
    devices_pool = NULL;
}

void *resource_pool_get_device(const char *name)
{
    void *resource = NULL;

    if(devices_pool) {
        resource = devices_pool->get_resource(devices_pool, name);
    }

    return resource;
}