/**
 * @file utest/cpputest/common/test_soft_timer.cpp
 *
 * Copyright (C) 2022
 *
 * test_soft_timer.cpp is free software: you can redistribute it and/or modify
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
#include "CppUTest/CommandLineTestRunner.h"
#include "soft_timer.h"

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
TEST_GROUP(soft_timer)
{
    timer_handle_t timer = nullptr;

    void setup(void)
    {
    }

    void teardown(void)
    {
        if(timer) {
            soft_timer_destroy(timer);
            timer = nullptr;
        }
    }

    void call_timer_ticks(uint32_t times)
    {
        while(times-- > 0) {
            soft_timer_tick();
            soft_timer_poll();
        }
    }
};

void timer_expired_cb(timer_handle_t timer)
{
    int32_t *pval = (int32_t *)soft_timer_get_user_data(timer);

    if(pval) {
        *pval = *pval - 1;
    }
}

TEST(soft_timer, NothingHappendAfterSoftTimerInit)
{
}

TEST(soft_timer, CreateSoftTimerWithNoName)
{
    uint32_t temp = 0;

    timer = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1000, &temp, timer_expired_cb);
    CHECK_FALSE(nullptr == timer);
}

TEST(soft_timer, CreateTimerWithPeriodIsZero)
{
    uint32_t temp = 0;

    timer = soft_timer_create("ZeroPeriodTimer", SFTIM_MODE_SINGLE, 0, &temp, timer_expired_cb);
    CHECK_TRUE(nullptr == timer);
}

TEST(soft_timer, CreateTimerWithNoCallback)
{
    uint32_t temp = 0;

    timer = soft_timer_create("ZeroPeriodTimer", SFTIM_MODE_SINGLE, 1000, &temp, nullptr);
    CHECK_FALSE(nullptr == timer);
}

TEST(soft_timer, CreateTimerWithoutUserData)
{
    timer = soft_timer_create("WithoutUserData", SFTIM_MODE_SINGLE, 1000, nullptr, timer_expired_cb);
    CHECK_FALSE(nullptr == timer);
}

TEST(soft_timer, CreateTimerWithErrorReloadMode)
{
    timer = soft_timer_create(nullptr, (soft_timer_mode_t)(SFTIM_MODE_REPEAT + 1), 1000, nullptr, timer_expired_cb);
    CHECK_TRUE(nullptr == timer);
}

TEST(soft_timer, DormatStateAfterCreate)
{
    timer = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1000, nullptr, timer_expired_cb);
    CHECK_FALSE(soft_timer_is_active(timer));
}

TEST(soft_timer, AcitveStateAfterStart)
{
    timer = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1000, nullptr, timer_expired_cb);
    soft_timer_start(timer);
    CHECK_TRUE(soft_timer_is_active(timer));
}

TEST(soft_timer, DormatStateAfterOneShotTimerExpired)
{
    timer = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1, nullptr, timer_expired_cb);
    soft_timer_start(timer);
    soft_timer_tick();
    CHECK_FALSE(soft_timer_is_active(timer));
}

TEST(soft_timer, OneShotTimerWillExpiredOnce)
{
    uint32_t value = 10;

    timer = soft_timer_create("OnePeriodTimer", SFTIM_MODE_SINGLE, 1, &value, timer_expired_cb);
    soft_timer_start(timer);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, value);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, value);
}

TEST(soft_timer, AutoReloadTimerWillExpiresAllways)
{
    uint32_t value = 100;

    timer = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 1, &value, timer_expired_cb);
    soft_timer_start(timer);
    call_timer_ticks(value);
    LONGS_EQUAL(0, value);
}

TEST(soft_timer, DestoryTimer)
{
    uint32_t value = 10;

    timer = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 1, &value, timer_expired_cb);
    soft_timer_start(timer);
    call_timer_ticks(1);
    LONGS_EQUAL(9, value);
    soft_timer_destroy(timer);
    timer = nullptr;
    call_timer_ticks(1);
    LONGS_EQUAL(9, value);
}

TEST(soft_timer, StopTimer)
{
    uint32_t value = 10;

    timer = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 1, &value, timer_expired_cb);
    soft_timer_start(timer);
    call_timer_ticks(1);
    LONGS_EQUAL(9, value);
    soft_timer_stop(timer);
    timer = nullptr;
    call_timer_ticks(1);
    LONGS_EQUAL(9, value);
}

TEST(soft_timer, RestartTimer)
{
    uint32_t value = 10;

    timer = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 2, &value, timer_expired_cb);
    soft_timer_start(timer);
    call_timer_ticks(1);
    soft_timer_restart(timer);
    call_timer_ticks(1);
    LONGS_EQUAL(10, value);
    call_timer_ticks(1);
    LONGS_EQUAL(9, value);
}

TEST(soft_timer, CreateTwoOneShotTimer)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;
    timer_handle_t timer1 = nullptr, timer2 = nullptr;

    timer2 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 2, &two_period_value, timer_expired_cb);
    timer1 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1, &one_period_value, timer_expired_cb);
    soft_timer_start(timer1);
    soft_timer_start(timer2);
    call_timer_ticks(1);
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(10, two_period_value);
    CHECK_FALSE(soft_timer_is_active(timer1));
    call_timer_ticks(1);
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    CHECK_FALSE(soft_timer_is_active(timer2));
    soft_timer_destroy(timer1);
    soft_timer_destroy(timer2);
}

TEST(soft_timer, CreateMultiSingleSoftTimer)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;
    uint32_t five_period_value = 10;
    uint32_t ten_period_value = 10;
    timer_handle_t timer1 = nullptr, timer2 = nullptr, timer3 = nullptr, timer4 = nullptr;

    timer4 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 10, &ten_period_value, timer_expired_cb);
    timer3 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 5, &five_period_value, timer_expired_cb);
    timer2 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 2, &two_period_value, timer_expired_cb);
    timer1 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1, &one_period_value, timer_expired_cb);
    soft_timer_start(timer3);
    soft_timer_start(timer1);
    soft_timer_start(timer2);
    soft_timer_start(timer4);
    call_timer_ticks(1);
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(10, two_period_value);
    LONGS_EQUAL(10, five_period_value);
    LONGS_EQUAL(10, ten_period_value);
    call_timer_ticks(1);
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    LONGS_EQUAL(10, five_period_value);
    LONGS_EQUAL(10, ten_period_value);
    call_timer_ticks(3);
    CHECK_FALSE(soft_timer_is_active(timer2));
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    LONGS_EQUAL(9, five_period_value);
    LONGS_EQUAL(10, ten_period_value);
    call_timer_ticks(5);
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    LONGS_EQUAL(9, five_period_value);
    LONGS_EQUAL(9, ten_period_value);
    soft_timer_destroy(timer1);
    soft_timer_destroy(timer2);
    soft_timer_destroy(timer3);
    soft_timer_destroy(timer4);
}

TEST(soft_timer, CreateTwoOneShotTimerWithSamePeriod)
{
    uint32_t value1 = 10;
    uint32_t value2 = 10;
    timer_handle_t timer1 = nullptr, timer2 = nullptr;

    timer1 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1, &value1, timer_expired_cb);
    timer2 = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 1, &value2, timer_expired_cb);
    soft_timer_start(timer1);
    soft_timer_start(timer2);
    call_timer_ticks(1);
    LONGS_EQUAL(9, value1);
    LONGS_EQUAL(9, value2);
    soft_timer_destroy(timer1);
    soft_timer_destroy(timer2);
}

TEST(soft_timer, CreateMultiAutoRealodTimer)
{
    int32_t ten_period_repeat_value = 100;
    int32_t three_period_repeat_value = 100;
    int32_t period_13th_single_value = 100;
    int32_t eight_period_repeat_value = 100;
    timer_handle_t timer1 = nullptr, timer2 = nullptr, timer3 = nullptr, timer4 = nullptr;

    timer4 = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 8, &eight_period_repeat_value, timer_expired_cb);
    timer3 = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 13, &period_13th_single_value, timer_expired_cb);
    timer2 = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 10, &ten_period_repeat_value, timer_expired_cb);
    timer1 = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 3, &three_period_repeat_value, timer_expired_cb);
    soft_timer_start(timer1);
    soft_timer_start(timer2);
    soft_timer_start(timer3);
    soft_timer_start(timer4);
    call_timer_ticks(1000);
    LONGS_EQUAL(100 - (1000 / 3), three_period_repeat_value);
    LONGS_EQUAL(100 - (1000 / 8), eight_period_repeat_value);
    LONGS_EQUAL(100 - (1000 / 10), ten_period_repeat_value);
    LONGS_EQUAL(100 - (1000 / 13), period_13th_single_value);
    soft_timer_destroy(timer1);
    soft_timer_destroy(timer2);
    soft_timer_destroy(timer3);
    soft_timer_destroy(timer4);
}

TEST(soft_timer, ChangePeriod)
{
    int32_t value = 100;
    
    timer = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 10, &value, timer_expired_cb);
    soft_timer_start(timer);
    soft_timer_change_period(timer, 100);
    call_timer_ticks(100);
    LONGS_EQUAL(99, value);
    soft_timer_destroy(timer);
}

TEST(soft_timer, ChangeReloadModeToOneShot)
{
    int32_t value = 100;

    timer = soft_timer_create(nullptr, SFTIM_MODE_REPEAT, 10, &value, timer_expired_cb);
    soft_timer_start(timer);
    call_timer_ticks(100);
    LONGS_EQUAL(90, value);
    soft_timer_set_reload_mode(timer, SFTIM_MODE_SINGLE);
    LONGS_EQUAL(SFTIM_MODE_SINGLE, soft_timer_get_reload_mode(timer));
    call_timer_ticks(100);
    LONGS_EQUAL(89, value);
}

TEST(soft_timer, ChangeReloadModeToAutoReaload)
{
    int32_t value = 100;

    timer = soft_timer_create(nullptr, SFTIM_MODE_SINGLE, 10, &value, timer_expired_cb);
    soft_timer_start(timer);
    call_timer_ticks(100);
    LONGS_EQUAL(99, value);
    soft_timer_set_reload_mode(timer, SFTIM_MODE_REPEAT);
    soft_timer_start(timer);
    LONGS_EQUAL(SFTIM_MODE_REPEAT, soft_timer_get_reload_mode(timer));
    call_timer_ticks(100);
    LONGS_EQUAL(89, value);
}