/**
 * @file utils\include\pingpong_buffer.h
 *
 * Copyright (C) 2021
 *
 * pingpong_buffer.h is free software: you can redistribute it and/or modify
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
#ifndef __PINGPONG_BUFFER_H
#define __PINGPONG_BUFFER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
/*---------- type define ----------*/
struct pingpong_buffer {
    void *buffer[2];
    volatile uint8_t write_index;
    volatile uint8_t read_index;
    volatile uint8_t read_avaliable[2];
};

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void pingpong_buffer_init(struct pingpong_buffer *handler, void *buf0, void *buf1);
extern bool pingpong_buffer_get_read_buf(struct pingpong_buffer *handler, void **pread_buf);
extern void pingpong_buffer_set_read_done(struct pingpong_buffer *handler);
extern void pingpong_buffer_get_write_buf(struct pingpong_buffer *handler, void **pwrite_buf);
extern void pingpong_buffer_set_write_done(struct pingpong_buffer *handler);

#ifdef __cplusplus
}
#endif
#endif /* __PINGPONG_BUFFER_H */
