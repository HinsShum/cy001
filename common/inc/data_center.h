/**
 * @file common/inc/data_center.h
 *
 * Copyright (C) 2022
 *
 * data_center.h is free software: you can redistribute it and/or modify
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
#ifndef __DATA_CENTER_H
#define __DATA_CENTER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "account.h"
#include "list.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
struct data_center {
    const char *name;                   /*<< The name of the data center will be used as the ID of the main account */
    struct account account_main;        /*<< Main account, will automaticatlly follow all acoounts */
    struct list_head account_pool;
    struct {
        bool (*add_account)(data_center_t center, account_t account);
        bool (*remove_account)(data_center_t center, account_t account);
        bool (*remove)(struct list_head *pool, account_t account);
        account_t (*search_account)(data_center_t center, const char *id);
        account_t (*find)(struct list_head *pool, const char *id);
        uint32_t (*get_account_count)(data_center_t center);
    } ops;
};

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void data_center_init(data_center_t center, const char *name);

#ifdef __cplusplus
}
#endif
#endif /* __DATA_CENTER_H */
