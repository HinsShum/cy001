/**
 * @file app\resource\resource_pool.c
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
#include "resource_pool.h"
#include "resource_manager.h"
#include "key_processing.h"
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

#define IMPORT_KEYS(name, pool)                                         \
        do {                                                            \
            void *dev = resource_pool_get_device(#name);                \
            assert(dev);                                                \
            if(dev) {                                                   \
                void *key = key_processing_create(dev);                 \
                assert(key);                                            \
                if(key) {                                               \
                    pool->add_resource(pool, #name, key);               \
                }                                                       \
            }                                                           \
        } while(0)

#define EXPORT_KEYS(name, pool)                                         \
        do {                                                            \
            void *key = pool->get_resource(pool, #name);                \
            assert(key);                                                \
            if(key) {                                                   \
                key_processing_destroy(key);                            \
                pool->remove_resource(pool, #name);                     \
            }                                                           \
        } while(0)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static resource_manager_base_t devices_pool;
static resource_manager_base_t keys_pool;

/*---------- function ----------*/
static void _resource_add(void)
{
    /* import devices */
    driver_search_device();
    IMPORT_DEVICE(com, devices_pool);
    IMPORT_DEVICE(flash1, devices_pool);
    IMPORT_DEVICE(flash2, devices_pool);
    IMPORT_DEVICE(wdt, devices_pool);
    IMPORT_DEVICE(keyup, devices_pool);
    IMPORT_DEVICE(key0, devices_pool);
    IMPORT_DEVICE(key1, devices_pool);
    IMPORT_DEVICE(key2, devices_pool);
    /* import key process */
    IMPORT_KEYS(keyup, keys_pool);
    IMPORT_KEYS(key0, keys_pool);
    IMPORT_KEYS(key1, keys_pool);
    IMPORT_KEYS(key2, keys_pool);
}

static void _resource_remove(void)
{
    /* export devices */
    EXPORT_DEVICE(com, devices_pool);
    EXPORT_DEVICE(flash1, devices_pool);
    EXPORT_DEVICE(flash2, devices_pool);
    EXPORT_DEVICE(wdt, devices_pool);
    EXPORT_DEVICE(keyup, devices_pool);
    EXPORT_DEVICE(key0, devices_pool);
    EXPORT_DEVICE(key1, devices_pool);
    EXPORT_DEVICE(key2, devices_pool);
    /* export keys */
    EXPORT_KEYS(keyup, keys_pool);
    EXPORT_KEYS(key0, keys_pool);
    EXPORT_KEYS(key1, keys_pool);
    EXPORT_KEYS(key2, keys_pool);
}

void resource_pool_init(void)
{
    /* create resource pool */
    if(devices_pool) {
        resource_manager_destroy(devices_pool);
    }
    devices_pool = resource_manager_create();
    assert(devices_pool);
    if(keys_pool) {
        resource_manager_destroy(keys_pool);
    }
    keys_pool = resource_manager_create();
    assert(keys_pool);
    /* add all resource */
    _resource_add();
}

void resource_pool_deinit(void)
{
    /* remove all resource */
    _resource_remove();
    resource_manager_destroy(devices_pool);
    devices_pool = NULL;
    resource_manager_destroy(keys_pool);
    keys_pool = NULL;
}

void *resource_pool_get_device(const char *name)
{
    void *resource = NULL;

    if(devices_pool) {
        resource = devices_pool->get_resource(devices_pool, name);
    }

    return resource;
}

void *resource_pool_get_device_careful(const char *name)
{
    void *resource = NULL;

    if(devices_pool) {
        resource = devices_pool->get_resource_careful(devices_pool, name);
    }

    return resource;
}

void *resource_pool_get_key(const char *name)
{
    void *key = NULL;

    if(keys_pool) {
        key = keys_pool->get_resource(keys_pool, name);
    }

    return key;
}

void *resource_pool_get_key_careful(const char *name)
{
    void *key = NULL;

    if(keys_pool) {
        key = keys_pool->get_resource_careful(keys_pool, name);
    }

    return key;
}
