/**
 * @file utils\pingpong_buffer.c
 *
 * Copyright (C) 2021
 *
 * pingpong_buffer.c is free software: you can redistribute it and/or modify
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
#include "pingpong_buffer.h"
#include <string.h>

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
/**
 * @brief Ping-pong buffer initialization.
 * @param handler: Pointer to the ping-pong buffer.
 * @param buf0: Pointer to the first buffer.
 * @param buf1: Pointer to the second buffer.
 * @retval None
 */
void pingpong_buffer_init(struct pingpong_buffer *handler, void *buf0, void *buf1)
{
    memset(handler, 0, sizeof(*handler));
    handler->buffer[0] = buf0;
    handler->buffer[1] = buf1;
}

/**
 * @brief Get a readable buffer.
 * @param handler: Pointer to the ping-pong buffer.
 * @param pread_buf: Pointer to the pointer to the buffer to be read.
 * @retval Returns true if there is a buffer to read.
 */
bool pingpong_buffer_get_read_buf(struct pingpong_buffer *handler, void **pread_buf)
{
    bool retval = true;

    if(handler->read_avaliable[0]) {
        handler->read_index = 0;
    } else if(handler->read_avaliable[1]) {
        handler->read_index = 1;
    } else {
        retval = false;
    }
    if(retval) {
        *pread_buf = handler->buffer[handler->read_index];
    }

    return retval;
}

/**
 * @brief Notify buffer read completion.
 * @param handler: Pointer to the ping-pong buffer.
 * @retval None
 */
void pingpong_buffer_set_read_done(struct pingpong_buffer *handler)
{
    handler->read_avaliable[handler->read_index] = false;
}

/**
 * @brief Get writable buffer.
 * @param handler: Pointer to the ping-pong buffer.
 * @param pwrite_buf: Pointer to the ponter to the buffer to be write.
 * @retval None
 */
void pingpong_buffer_get_write_buf(struct pingpong_buffer *handler, void **pwrite_buf)
{
    if(handler->write_index == handler->read_index) {
        handler->write_index = !handler->read_index;
    }
    *pwrite_buf = handler->buffer[handler->write_index];
}

/**
 * @brief Notify buffer write completion.
 * @param handler: Pointer to the ping-pong buffer.
 * @retval None
 */
void pingpong_buffer_set_write_done(struct pingpong_buffer *handler)
{
    handler->read_avaliable[handler->write_index] = true;
    handler->write_index = !handler->write_index;
}
