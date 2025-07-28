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
#include "freertos/event_groups.h"


#define BIT_0 ( 1 << 0 ) 
#define BIT_4 ( 1 << 4 ) 
 EventGroupHandle_t  event_handle=NULL;

void Task1(void *param)
{
    while (1)
    {
        printf("Task1: Waiting for bits to be set...\n");
        EventBits_t uxBits = xEventGroupWaitBits( event_handle, /* The event group being tested. */ 
        BIT_0 | BIT_4,  /* The bits within the event group to wait for. */ 
        pdTRUE, /* BIT_0 and BIT_4 should be cleared before returning. */
        pdTRUE, /* wait for both bits */ 
        portMAX_DELAY); /* Wait a maximum amount of time for either bit to be set. */
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("Task1: Bits returned: 0x%" PRIx32 "\n", uxBits);

    }
}
void Task2(void *param)
{

    while (1)
    {
        printf("Task2: Setting bits...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xEventGroupSetBits(event_handle, BIT_0 );
        printf("Task2: Set BIT_0\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
        xEventGroupSetBits(event_handle, BIT_4 );
        printf("Task2: Set BIT_4\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void app_main(void)
{
    event_handle=xEventGroupCreate(  ); 
    if (!event_handle) {
        printf("Failed to create event group\n");
        return;
    }
    xTaskCreate(Task1, "Task1", 4096, (void*)(intptr_t)3, 1, NULL);
    xTaskCreate(Task2, "Task2", 4096, (void*)(intptr_t)3, 1, NULL);
}