/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
static SemaphoreHandle_t handle_mutex = NULL;
static int counter = 0;

/* Helper: does the recursion */
static void recurse_and_run(int depth) {
    xSemaphoreTakeRecursive(handle_mutex, portMAX_DELAY);
    printf("%s: depth=%d  counter→%d\n",
           pcTaskGetName(NULL), depth, ++counter);

    if (depth > 0) {
        recurse_and_run(depth - 1);
    }

    xSemaphoreGiveRecursive(handle_mutex);
}

void Task1(void *param)
{
    /* Un‑pack your start value safely */
    int startvalue = (int)(intptr_t)param;
    recurse_and_run(startvalue);

    /* Now that all recursion has unwound, delete self */
    vTaskDelete(NULL);
}

void app_main(void)
{
    handle_mutex = xSemaphoreCreateRecursiveMutex();
    if (!handle_mutex) {
        printf("Failed to create recursive mutex\n");
        return;
    }

    /* Two tasks both recursing 3 levels deep: Task2 blocks until Task1 fully finishes */
    xTaskCreate(Task1, "Task1", 4096, (void*)(intptr_t)3, 1, NULL);
    xTaskCreate(Task1, "Task2", 4096, (void*)(intptr_t)3, 1, NULL);
}