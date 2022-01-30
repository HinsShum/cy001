/**
 * @file boards\cy001\bsp\bsp_key1.c
 *
 * Copyright (C) 2022
 *
 * bsp_key1.c is free software: you can redistribute it and/or modify
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
#include "bsp_key.h"
#include "gpio.h"
#include "stm32f1xx.h"
#include "stm32f1xx_ll_conf.h"

/*---------- macro ----------*/
#define CONFIG_GPIO_PORT            (GPIOE)
#define CONFIG_GPIO_PIN             (LL_GPIO_PIN_3)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
static bool bsp_init(void);
static void bsp_deinit(void);
static bool bsp_get(void);

/*---------- variable ----------*/
static gpio_describe_t key = {
    .ops.init = bsp_init,
    .ops.deinit = bsp_deinit,
    .ops.get = bsp_get,
    .ops.set = NULL,
    .ops.toggle = NULL,
    .ops.irq_handler = NULL
};
DEVICE_DEFINED(key1, gpio, &key);

/*---------- function ----------*/
static bool bsp_init(void)
{
    LL_GPIO_InitTypeDef gpio;

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
    while(true != LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GPIOE));
    LL_GPIO_StructInit(&gpio);
    gpio.Mode = LL_GPIO_MODE_INPUT;
    gpio.Pull = LL_GPIO_PULL_UP;
    gpio.Pin = CONFIG_GPIO_PIN;
    LL_GPIO_Init(CONFIG_GPIO_PORT, &gpio);

    return true;
}

static void bsp_deinit(void)
{
    LL_GPIO_InitTypeDef gpio;

    LL_GPIO_StructInit(&gpio);
    gpio.Pin = CONFIG_GPIO_PIN;
    gpio.Mode = LL_GPIO_MODE_OUTPUT;
    gpio.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio.Pull = LL_GPIO_PULL_UP;
    gpio.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(CONFIG_GPIO_PORT, &gpio);
    LL_GPIO_SetOutputPin(CONFIG_GPIO_PORT, CONFIG_GPIO_PIN);
}

static bool bsp_get(void)
{
    return (!LL_GPIO_IsInputPinSet(CONFIG_GPIO_PORT, CONFIG_GPIO_PIN));
}
