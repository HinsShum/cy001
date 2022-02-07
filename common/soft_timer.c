/**
 * @file common\soft_timer.c
 *
 * Copyright (C) 2022
 *
 * soft_timer.c is free software: you can redistribute it and/or modify
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
#include "soft_timer.h"
#include "list.h"
#include "options.h"
#include <string.h>

/*---------- macro ----------*/
#ifndef CONFIG_NUMBER_OF_SOFTTIMERS
#define CONFIG_NUMBER_OF_SOFTTIMERS             (10)
#endif

/*---------- type define ----------*/
struct timer_tcb {
    struct list_head node;
    uint8_t mode;
    const char *name;
    uint32_t remaining_time;
    uint32_t period;
    void *cb_data;
    void (*cb)(void *cb_data);
};

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static LIST_HEAD(_timer_active);
static LIST_HEAD(_timer_ready);
static LIST_HEAD(_timer_idle);
static struct timer_tcb _timer[CONFIG_NUMBER_OF_SOFTTIMERS];
static uint32_t _timer_count;

/*---------- function ----------*/
static inline void _lock(void)
{
    __enter_critical();
}

static inline void _unlock(void)
{
    __exit_critical();
}

static inline void _del_and_insert_to_idle(struct timer_tcb *tcb)
{
    list_del(&tcb->node);
    memset(tcb, 0, sizeof(*tcb));
    list_add_tail(&tcb->node, &_timer_idle);
}

static inline void _insert_to_idle(struct timer_tcb *tcb)
{
    memset(tcb, 0, sizeof(*tcb));
    list_add_tail(&tcb->node, &_timer_idle);
}

static inline void _del_and_insert_to_ready(struct timer_tcb *tcb)
{
    list_del(&tcb->node);
    list_add_tail(&tcb->node, &_timer_ready);
}

static struct timer_tcb *_find(const char *name, struct list_head *head)
{
    struct timer_tcb *p = NULL;
    struct timer_tcb *ret = NULL;

    _lock();
    list_for_each_entry(p, struct timer_tcb, head, node) {
        if(strcmp(p->name, name) == 0) {
            ret = p;
            break;
        }
    }
    _unlock();

    return ret;
}

static void _insert_to_active(struct timer_tcb *pnew)
{
    struct timer_tcb *p = NULL, *n = NULL;
    uint32_t remaining_time_total = 0;
    bool find_insert_point = false;

    _lock();
    if(list_empty_careful(&_timer_active) == true) {
        /* insert at the begin */
        list_add(&pnew->node, &_timer_active);
        pnew->remaining_time = pnew->period;
        _timer_count = pnew->remaining_time;
    } else {
        /* update the first soft timer remaining time */
        p = list_first_entry(&_timer_active, struct timer_tcb, node);
        p->remaining_time = _timer_count;
        list_for_each_entry(p, struct timer_tcb, &_timer_active, node) {
            remaining_time_total += p->remaining_time;
            if(remaining_time_total > pnew->period) {
                find_insert_point = true;
                break;
            }
        }
        if(find_insert_point == true) {
            /* insert in the middle */
            n = list_prev_entry(p, struct timer_tcb, node);
            list_add(&pnew->node, &n->node);
            remaining_time_total -= p->remaining_time;
            pnew->remaining_time = pnew->period - remaining_time_total;
            p->remaining_time = p->remaining_time - pnew->remaining_time;
        } else {
            /* insert at the end */
            pnew->remaining_time = pnew->period - remaining_time_total;
            list_add_tail(&pnew->node, &_timer_active);
        }
        /* update timer count */
        p = list_first_entry(&_timer_active, struct timer_tcb, node);
        _timer_count = p->remaining_time;
    }
    _unlock();
}

static void inline _remove_from_ready(struct timer_tcb *premove)
{
    _lock();
    _del_and_insert_to_idle(premove);
    _unlock();
}

static void _remove_from_active(struct timer_tcb *premove)
{
    struct timer_tcb *next_tcb = NULL;
    struct timer_tcb *p = NULL;

    _lock();
    /* update the first soft timer remaining time */
    p = list_first_entry(&_timer_active, struct timer_tcb, node);
    p->remaining_time = _timer_count;
    if(list_last_entry(&_timer_active, struct timer_tcb, node) != premove) {
        next_tcb = list_next_entry(premove, struct timer_tcb, node);
        next_tcb->remaining_time += premove->remaining_time;
    }
    _del_and_insert_to_idle(premove);
    /* update timer count */
    p = list_first_entry(&_timer_active, struct timer_tcb, node);
    _timer_count = p->remaining_time;
    _unlock();
}

void soft_timer_init(void)
{
    INIT_LIST_HEAD(&_timer_idle);
    INIT_LIST_HEAD(&_timer_active);
    INIT_LIST_HEAD(&_timer_ready);
    for(uint32_t i = 0; i < CONFIG_NUMBER_OF_SOFTTIMERS; ++i) {
        memset(&_timer[i], 0, sizeof(struct timer_tcb));
        list_add_tail(&_timer[i].node, &_timer_idle);       
    }
}

void soft_timer_deinit(void)
{
    struct timer_tcb *p = NULL, *n = NULL;

    _lock();
    /* Make sure the update timer event will not be fired */
    _timer_count = 0;
    _unlock();
    if(list_empty_careful(&_timer_active) != true) {
        list_for_each_entry_safe(p, n, struct timer_tcb, &_timer_active, node) {
            __debug_message("SoftTimer: remove %s[0x%p] from active list\n", p->name, p);
            _del_and_insert_to_idle(p);
        }
    }
    if(list_empty_careful(&_timer_ready) != true) {
        list_for_each_entry_safe(p, n, struct timer_tcb, &_timer_ready, node) {
            __debug_message("SoftTimer: remove %s[0x%p] from ready list\n", p->name, p);
            _del_and_insert_to_idle(p);
        }
    }
}

int32_t soft_timer_create(const char *name, uint8_t mode, uint32_t period, void *cb_data, void (*cb)(void *cb_data))
{
    int32_t retval = -SOFTTIMER_ERR_FULL;
    struct timer_tcb *tcb = NULL;

    do {
        if(name == NULL || period == 0 || cb == NULL) {
            retval = -SOFTTIMER_ERR_ERROR;
            break;
        }
        if(_find(name, &_timer_active) || _find(name, &_timer_ready)) {
            retval = -SOFTTIMER_ERR_EXIT;
            break;
        }
        if(list_empty_careful(&_timer_idle)) {
            __debug_warn("SoftTimer: no enough memory to create a new soft timer\n");
            break;
        }
        _lock();
        tcb = list_first_entry(&_timer_idle, struct timer_tcb, node);
        list_del(&tcb->node);
        _unlock();
        tcb->name = name;
        tcb->mode = mode;
        tcb->period = period;
        tcb->cb_data = cb_data;
        tcb->cb = cb;
        _insert_to_active(tcb);
        retval = SOFTTIMER_ERR_OK;
    } while(0);

    return retval;
}

int32_t soft_timer_destroy(const char *name)
{
    int32_t retval = -SOFTTIMER_ERR_NOT_FOUND;
    struct timer_tcb *p = NULL;

    do {
        p = _find(name, &_timer_ready);
        if(p != NULL) {
            retval = SOFTTIMER_ERR_OK;
            _remove_from_ready(p);
            break;
        }
        p = _find(name, &_timer_active);
        if(p == NULL) {
            break;
        }
        _remove_from_active(p);
        retval = SOFTTIMER_ERR_OK;
    } while(0);

    return retval;
}

void soft_timer_poll(void)
{
    struct timer_tcb *tcb = NULL;

    while(list_empty_careful(&_timer_ready) != true) {
        _lock();
        tcb = list_first_entry(&_timer_ready, struct timer_tcb, node);
        list_del(&tcb->node);
        _unlock();
        tcb->cb(tcb->cb_data);
        if(tcb->mode == SOFTTIMER_MODE_REPEAT) {
            _insert_to_active(tcb);
        } else {
            _insert_to_idle(tcb);
        }
    }
}

void soft_timer_tick(void)
{
    struct timer_tcb *tcb = NULL, *next_tcb;;

    _timer_count--;
    if(_timer_count == 0 && list_empty_careful(&_timer_active) != true) {
        /* soft timer due now */
        tcb = list_first_entry(&_timer_active, struct timer_tcb, node);
        tcb->remaining_time = 0;
        _lock();
        list_for_each_entry_safe(tcb, next_tcb, struct timer_tcb, &_timer_active, node) {
            if(tcb->remaining_time == 0) {
                _del_and_insert_to_ready(tcb);
                continue;
            }
            _timer_count = tcb->remaining_time;
            break;
        }
        _unlock();
    }
}
