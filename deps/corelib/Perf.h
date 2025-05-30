#pragma once

#include "stdio.h"
#include "SysHelper.h"

#define PERF_1_START()                           \
{                                                \
    int count1 = 10;                             \
    int count2 = 50;                             \
    int count3 = 100;                            \
    for (int k0 = 0; k0 < count1; k0++)          \
    {                                            \
        long sum = 0;                            \
        for (int k1 = 0; k1 < count2; k1++)      \
        {                                        \
            long time1 = SysHelperGetTime();     \
            for (int k2 = 0; k2 < count3; k2++)  \
            {

#define PERF_1_END()                             \
            }                                    \
            long time2 = SysHelperGetTime();     \
            long diff = time2 - time1;           \
            sum += diff;                         \
            printf("-");                         \
        }                                        \
        long avg = sum / count2;                 \
        printf(" %i\n", avg);                    \
    }                                            \
}

long REC_SUM = 0;
long REC_COUNT = 0;

#define REC_1                                  \
{                                              \
    long time1 = SysHelperGetTime();           \

#define REC_2                                  \
    long time2 = SysHelperGetTime();           \
    REC_SUM += time2 - time1;                  \
    REC_COUNT++;                               \
    if (REC_COUNT == 50)                       \
    {                                          \
        printf("PERF:%li\n", REC_SUM / REC_COUNT); \
        REC_COUNT = 0;                         \
        REC_SUM = 0;                           \
    }                                          \
}

#define TEST_1_CALLCOUNT 50
long    TEST_1_SUM      = 0;
long    TEST_1_COUNT    = 0;
long    TEST_1_TIME_OLD = 0;
long    TEST_1_TIME_NEW = 0;

void REC_LOOP()
{
    printf("-");

    TEST_1_TIME_NEW = SysHelperGetTime();
    TEST_1_SUM += TEST_1_TIME_NEW - TEST_1_TIME_OLD;
    TEST_1_TIME_OLD = TEST_1_TIME_NEW;
    TEST_1_COUNT++;

    if (TEST_1_COUNT != TEST_1_CALLCOUNT) return;

    printf(" %li\n", TEST_1_SUM / TEST_1_COUNT);
    TEST_1_SUM = 0;
    TEST_1_COUNT = 0;
}
