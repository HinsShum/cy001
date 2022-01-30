/**
 * @file common\key_processing.c
 *
 * Copyright (C) 2022
 *
 * key_processing.c is free software: you can redistribute it and/or modify
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
#include "key_processing.h"
#include "gpio.h"
#include "options.h"
#include <string.h>

/*---------- macro ----------*/
#define KEY_LONG_PRESS_TIME                 (500)       /*<< 500ms */
#define KEY_PRESSING_READ_PERIOD            (200)       /*<< 200ms */

/*---------- type define ----------*/
struct key_proc {
    bool pressed;
    bool released;
    bool last_key_value;
    uint64_t pressed_time;
    uint64_t pressing_time;
    uint32_t state;
    const void *device;
    void (*event_cb)(enum key_event event);
};

enum key_state {
    KEY_STATE_RELEASED,
    KEY_STATE_PRESSED = (1 << KEY_EVENT_PRESSED),
    KEY_STATE_PRESSING = (1 << KEY_EVENT_PRESSING),
    KEY_STATE_LONG_PRESSED = (1 << KEY_EVENT_LONG_PRESSED)
};

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
static inline bool _is_pressed(const key_proc_t key, bool key_value)
{
    bool retval = false;

    if(key_value && !key->pressed) {
        retval = true;
    }

    return retval;
}

static inline bool _is_pressing(const key_proc_t key, bool key_value)
{
    bool retval = false;

    if(key->pressed && key_value) {
        retval = true;
    }

    return retval;
}

static inline bool _is_released(const key_proc_t key, bool key_value)
{
    bool retval = false;

    if(!key_value && !key->released) {
        retval = true;
    }

    return retval;
}

static inline bool _is_key_stable(const key_proc_t key, bool key_value)
{
    return (key->last_key_value == key_value);
}

static void _key_event_cb_default(enum key_event event)
{
    /* do nothing */
}

key_proc_t key_processing_create(const void *device)
{
    key_proc_t key = NULL;

    do {
        key = __malloc(sizeof(struct key_proc));
        if(key == NULL) {
            __debug_error("No memory for alloc key processing\n");
            break;
        }
        __debug_message("Key Process: alloc 0x%p for new key\n", key);
        memset(key, 0, sizeof(*key));
        key->device = device;
        key->pressed = false;
        key->released = true;
        key->last_key_value = false;
        key->event_cb = _key_event_cb_default;
    } while(0);

    return key;
}

void key_processing_destroy(const key_proc_t key)
{
    if(key) {
        __free(key);
    }
}

void key_processing_set_event_cb(const key_proc_t key, void (*event_cb)(enum key_event event))
{
    if(key) {
        if(event_cb != NULL) {
            key->event_cb = event_cb;
        } else {
            key->event_cb = _key_event_cb_default;
        }
    }
}

void key_processing(const key_proc_t key)
{
    bool key_value = false;
    uint64_t cur_ticks = __get_ticks();
    const char *name = NULL;
    bool update = false;
    uint64_t pressing_time = 0;

    do {
        if(key == NULL || key->device == NULL) {
            break;
        }
        name = ((device_t *)key->device)->dev_name;
        /* check key value */
        device_ioctl((device_t *)key->device, IOCTL_GPIO_GET, &key_value);
        if(_is_key_stable(key, key_value) != true) {
            key->last_key_value = key_value;
            break;
        }
        update = true;
        if(_is_pressed(key, key_value)) {
            __debug_info("Key Process: %s pressed now\n", name);
            /* key pressed */
            key->state |= KEY_STATE_PRESSED;
            key->pressed_time = TICKS2MS(cur_ticks);
            key->pressing_time = 0;
            /* tigger pressed event */
            key->event_cb(KEY_EVENT_PRESSED);
            break;
        }
        pressing_time = TICKS2MS(cur_ticks) - key->pressed_time;
        if(_is_pressing(key, key_value)) {
            if((pressing_time - key->pressing_time) >= KEY_PRESSING_READ_PERIOD) {
                __debug_info("Key Process: %s pressing\n", name);
                key->pressing_time = pressing_time;
                key->state |= KEY_STATE_PRESSING;
                /* tigger pressing event */
                key->event_cb(KEY_EVENT_PRESSING);
            }
            if(pressing_time >= KEY_LONG_PRESS_TIME &&
               (key->state & KEY_STATE_LONG_PRESSED) == 0) {
                __debug_info("Key Process: %s long pressed\n", name);
                key->state |= KEY_STATE_LONG_PRESSED;
                /* tigger long pressed event */
                key->event_cb(KEY_EVENT_LONG_PRESSED);
            }
            break;
        }
        if(_is_released(key, key_value)) {
            if(pressing_time < KEY_LONG_PRESS_TIME) {
                __debug_info("Key Process: %s short clicked, released now\n", name);
                /* tigger short clicked event */
                key->event_cb(KEY_EVENT_SHORT_CLICKED);
            } else {
                __debug_info("Key Process: %s clicked, released now\n", name);
                /* tigger clicked event */
                key->event_cb(KEY_EVENT_CLICKED);
            }
            /* tigger released event */
            key->event_cb(KEY_EVENT_RELEASED);
            key->pressed_time = 0;
            key->pressing_time = 0;
            key->state = KEY_STATE_RELEASED;
        }
    } while(0);
    if(update) {
        key->pressed = key_value;
        key->released = !key_value;
    }
}
