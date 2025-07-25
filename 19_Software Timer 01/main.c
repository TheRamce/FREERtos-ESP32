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
#include "freertos/timers.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_task_wdt.h"

void vCallbackFunction( TimerHandle_t xTimer )
{
    printf("Timer ticked!\n");
}

void app_main(void)
{

    TimerHandle_t handle=NULL;
    
    handle= xTimerCreate( "mytimer",pdMS_TO_TICKS( 1000 ),pdTRUE,  (void *) 0,   vCallbackFunction );

    if (handle == NULL) {
        printf("Timer creation failed!\n");
    } else {
        printf("Timer created successfully!\n");
    }
    // Start the timer with a block time of 0 ticks.
    if (xTimerStart(handle, 0) != pdPASS) {
        printf("Timer start failed!\n");
    } else {
        printf("Timer started successfully!\n");
    }
    vTaskDelay(pdMS_TO_TICKS(5000)); // Wait for 5 seconds to see the timer callback in action

    // Stop the timer
    if (xTimerStop(handle, 0) != pdPASS) {
        printf("Timer stop failed!\n");
    } else {
        printf("Timer stopped successfully!\n");
    }
    vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 2 seconds before deleting the timer
    // Delete the timer
    if (xTimerDelete(handle, 0) != pdPASS) {
        printf("Timer delete failed!\n");
    } else {
        printf("Timer deleted successfully!\n");
    }
 



}
