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
    void setup(void)
    {
        soft_timer_init();
    }

    void teardown(void)
    {
        soft_timer_deinit();
    }

    void call_timer_ticks(uint32_t times)
    {
        while(times-- > 0) {
            soft_timer_tick();
        }
    }
};

void callback(void *cb_data)
{
    uint32_t *pvalue = (uint32_t *)cb_data;

    if(cb_data) {
        *pvalue = *pvalue - 1;
    }
}

TEST(soft_timer, NothingHappendAfterSoftTimerInit)
{
}

TEST(soft_timer, CreateSoftTimerWithNoName)
{
    LONGS_EQUAL(-SOFTTIMER_ERR_ERROR, soft_timer_create(NULL, SOFTTIMER_MODE_SINGLE, 10, NULL, NULL));
}

TEST(soft_timer, CreateSingleSoftTimerWithPeriodIsZero)
{
    LONGS_EQUAL(-SOFTTIMER_ERR_ERROR, soft_timer_create("ZeroPeriodTimer", SOFTTIMER_MODE_SINGLE, 0, NULL, NULL));

}

TEST(soft_timer, CreateSingleSoftTimerWithNoCallback)
{
    LONGS_EQUAL(-SOFTTIMER_ERR_ERROR, soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, NULL, NULL));
}

TEST(soft_timer, CreateOneSingleSoftTimerWithPeriodOne)
{
    uint32_t value = 10;

    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &value, callback));
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, value);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, value);
}

TEST(soft_timer, CreateOneRepeatSoftTimerWithPeriodOne)
{
    uint32_t value = 100;

    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("OneRepeatTimer", SOFTTIMER_MODE_REPEAT, 1, &value, callback));
    for(uint32_t i = 1; i < 100; i++) {
        soft_timer_tick();
        soft_timer_poll();
        LONGS_EQUAL(100, value + i);
    }
}

TEST(soft_timer, DestroyOneSoftTimerWithPeriodOneTestOne)
{
    uint32_t value = 10;

    soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &value, callback);
    soft_timer_tick();
    soft_timer_destroy("OnePeriodTimer");
    soft_timer_poll();
    LONGS_EQUAL(10, value);
}

TEST(soft_timer, DestroyOneSoftTimerWithPeriodOneTestTwo)
{
    uint32_t value = 10;

    soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &value, callback);
    soft_timer_destroy("OnePeriodTimer");
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(10, value);
}

TEST(soft_timer, CreateTwoSingleSoftTimerTestOne)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;

    soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &one_period_value, callback);
    soft_timer_create("TwoPeriodTimer", SOFTTIMER_MODE_SINGLE, 2, &two_period_value, callback);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(10, two_period_value);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
}

TEST(soft_timer, CreateTwoSingleSoftTimerTestTwo)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;

    soft_timer_create("TwoPeriodTimer", SOFTTIMER_MODE_SINGLE, 2, &two_period_value, callback);
    soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &one_period_value, callback);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(10, two_period_value);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
}

TEST(soft_timer, CreateMultiSingleSoftTimer)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;
    uint32_t five_period_value = 10;
    uint32_t ten_period_value = 10;

    soft_timer_create("FivePeriodTimer", SOFTTIMER_MODE_SINGLE, 5, &five_period_value, callback);
    soft_timer_create("OnePeriodTImer", SOFTTIMER_MODE_SINGLE, 1, &one_period_value, callback);
    soft_timer_create("TenPeriodTimer", SOFTTIMER_MODE_SINGLE, 10, &ten_period_value, callback);
    soft_timer_create("TwoPeriodTImer", SOFTTIMER_MODE_SINGLE, 2, &two_period_value, callback);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(10, two_period_value);
    LONGS_EQUAL(10, five_period_value);
    LONGS_EQUAL(10, ten_period_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    LONGS_EQUAL(10, five_period_value);
    LONGS_EQUAL(10, ten_period_value);
    call_timer_ticks(3);
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    LONGS_EQUAL(9, five_period_value);
    LONGS_EQUAL(10, ten_period_value);
    call_timer_ticks(5);
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(9, two_period_value);
    LONGS_EQUAL(9, five_period_value);
    LONGS_EQUAL(9, ten_period_value);
}

TEST(soft_timer, CreateTwoSingleSoftTimerWithSamePeriod)
{
    uint32_t value1 = 10;
    uint32_t value2 = 10;

    soft_timer_create("OnePeriodTImer1", SOFTTIMER_MODE_SINGLE, 1, &value1, callback);
    soft_timer_create("OnePeriodTImer2", SOFTTIMER_MODE_SINGLE, 1, &value2, callback);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(9, value1);
    LONGS_EQUAL(9, value2);
}

TEST(soft_timer, CreateTwoSoftTimerAndDestroyTwoPeriodTimer)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;

    soft_timer_create("TwoPeriodTimer", SOFTTIMER_MODE_SINGLE, 2, &two_period_value, callback);
    soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &one_period_value, callback);
    soft_timer_destroy("TwoPeriodTimer");
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(9, one_period_value);
    LONGS_EQUAL(10, two_period_value);
}

TEST(soft_timer, CreateTwoSoftTimerAndDestroyOnePeriodTimer)
{
    uint32_t one_period_value = 10;
    uint32_t two_period_value = 10;

    soft_timer_create("TwoPeriodTimer", SOFTTIMER_MODE_SINGLE, 2, &two_period_value, callback);
    soft_timer_create("OnePeriodTimer", SOFTTIMER_MODE_SINGLE, 1, &one_period_value, callback);
    soft_timer_destroy("OnePeriodTimer");
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(10, one_period_value);
    LONGS_EQUAL(10, two_period_value);
    soft_timer_tick();
    soft_timer_poll();
    LONGS_EQUAL(10, one_period_value);
    LONGS_EQUAL(9, two_period_value);
}

TEST(soft_timer, CreateTwoSameNameSoftTimer)
{
    soft_timer_create("Timer", SOFTTIMER_MODE_SINGLE, 1, NULL, callback);
    LONGS_EQUAL(-SOFTTIMER_ERR_EXIT, soft_timer_create("Timer", SOFTTIMER_MODE_REPEAT, 10, NULL, callback));
}

TEST(soft_timer, DestroySoftTimerNotCreateBefore)
{
    LONGS_EQUAL(-SOFTTIMER_ERR_NOT_FOUND, soft_timer_destroy("TImer"));
}

TEST(soft_timer, CreateSoftTimerNumbersOverBound)
{
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("1", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("2", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("3", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("4", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("5", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("6", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("7", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("8", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("9", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(SOFTTIMER_ERR_OK, soft_timer_create("10", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
    LONGS_EQUAL(-SOFTTIMER_ERR_FULL, soft_timer_create("11", SOFTTIMER_MODE_SINGLE, 1, NULL, callback));
}

TEST(soft_timer, CreateMultiRepeateSoftTimer)
{
    uint32_t ten_period_repeat_value = 100;
    uint32_t three_period_repeat_value = 100;
    uint32_t period_13th_single_value = 100;
    uint32_t eight_period_repeat_value = 100;

    soft_timer_create("TenPeriodRepeatTimer", SOFTTIMER_MODE_REPEAT, 10, &ten_period_repeat_value, callback);
    soft_timer_create("ThreePeriodRepeatTimer", SOFTTIMER_MODE_REPEAT, 3, &three_period_repeat_value, callback);
    soft_timer_create("13thPeriodSingleTImer", SOFTTIMER_MODE_SINGLE, 13, &period_13th_single_value, callback);
    soft_timer_create("EightPeriodRepeatTimer", SOFTTIMER_MODE_REPEAT, 8, &eight_period_repeat_value, callback);
    call_timer_ticks(3);
    soft_timer_poll();
    LONGS_EQUAL(99, three_period_repeat_value);
    LONGS_EQUAL(100, eight_period_repeat_value);
    LONGS_EQUAL(100, ten_period_repeat_value);
    LONGS_EQUAL(100, period_13th_single_value);
    call_timer_ticks(3);
    soft_timer_poll();
    LONGS_EQUAL(98, three_period_repeat_value);
    LONGS_EQUAL(100, eight_period_repeat_value);
    LONGS_EQUAL(100, ten_period_repeat_value);
    LONGS_EQUAL(100, period_13th_single_value);
    call_timer_ticks(2);
    soft_timer_poll();
    LONGS_EQUAL(98, three_period_repeat_value);
    LONGS_EQUAL(99, eight_period_repeat_value);
    LONGS_EQUAL(100, ten_period_repeat_value);
    LONGS_EQUAL(100, period_13th_single_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(97, three_period_repeat_value);
    LONGS_EQUAL(99, eight_period_repeat_value);
    LONGS_EQUAL(100, ten_period_repeat_value);
    LONGS_EQUAL(100, period_13th_single_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(97, three_period_repeat_value);
    LONGS_EQUAL(99, eight_period_repeat_value);
    LONGS_EQUAL(99, ten_period_repeat_value);
    LONGS_EQUAL(100, period_13th_single_value);
    call_timer_ticks(2);
    soft_timer_poll();
    LONGS_EQUAL(96, three_period_repeat_value);
    LONGS_EQUAL(99, eight_period_repeat_value);
    LONGS_EQUAL(99, ten_period_repeat_value);
    LONGS_EQUAL(100, period_13th_single_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(96, three_period_repeat_value);
    LONGS_EQUAL(99, eight_period_repeat_value);
    LONGS_EQUAL(99, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(2);
    soft_timer_poll();
    LONGS_EQUAL(95, three_period_repeat_value);
    LONGS_EQUAL(99, eight_period_repeat_value);
    LONGS_EQUAL(99, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(95, three_period_repeat_value);
    LONGS_EQUAL(98, eight_period_repeat_value);
    LONGS_EQUAL(99, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(2);
    soft_timer_poll();
    LONGS_EQUAL(94, three_period_repeat_value);
    LONGS_EQUAL(98, eight_period_repeat_value);
    LONGS_EQUAL(99, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(2);
    soft_timer_poll();
    LONGS_EQUAL(94, three_period_repeat_value);
    LONGS_EQUAL(98, eight_period_repeat_value);
    LONGS_EQUAL(98, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(93, three_period_repeat_value);
    LONGS_EQUAL(98, eight_period_repeat_value);
    LONGS_EQUAL(98, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(3);
    soft_timer_poll();
    LONGS_EQUAL(92, three_period_repeat_value);
    LONGS_EQUAL(97, eight_period_repeat_value);
    LONGS_EQUAL(98, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(2);
    soft_timer_poll();
    LONGS_EQUAL(92, three_period_repeat_value);
    LONGS_EQUAL(97, eight_period_repeat_value);
    LONGS_EQUAL(98, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(1);
    soft_timer_poll();
    LONGS_EQUAL(91, three_period_repeat_value);
    LONGS_EQUAL(97, eight_period_repeat_value);
    LONGS_EQUAL(98, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
    call_timer_ticks(3);
    soft_timer_poll();
    LONGS_EQUAL(90, three_period_repeat_value);
    LONGS_EQUAL(97, eight_period_repeat_value);
    LONGS_EQUAL(97, ten_period_repeat_value);
    LONGS_EQUAL(99, period_13th_single_value);
}
