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

#define TASK_0_BIT        ( 1 << 0 ) 
#define TASK_1_BIT        ( 1 << 1 ) 
#define TASK_2_BIT        ( 1 << 2 ) 
 
#define ALL_SYNC_BITS ( TASK_0_BIT | TASK_1_BIT | TASK_2_BIT )
 EventGroupHandle_t  event_handle=NULL;

void Task1(void *param)
{
    while (1)
    {
        printf("Task1 is running  \n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        printf("Task1 is setting bit TASK_0_BIT\n");

        EventBits_t uxReturn = xEventGroupSync( event_handle,  
                                    TASK_0_BIT,    /* The bit to set. */ 
                                    ALL_SYNC_BITS, /* The bits to wait for. */ 
                                    portMAX_DELAY );/* Timeout value. */
        
        printf("Task1 is syncing\n");
        vTaskDelay(pdMS_TO_TICKS(5000));

    }
}
void Task2(void *param)
{

    while (1)
    {
        printf("Task2 is running  \n");
        vTaskDelay(pdMS_TO_TICKS(3000));

        printf("Task2 is setting bit TASK_1_BIT\n");

        EventBits_t uxReturn = xEventGroupSync( event_handle,  
                                    TASK_1_BIT,    /* The bit to set. */ 
                                    ALL_SYNC_BITS, /* The bits to wait for. */ 
                                    portMAX_DELAY );/* Timeout value. */
        
        printf("Task2 is syncing\n");


    } 
}
    

void Task3(void *param)
{

    while (1)
    {
        printf("Task3 is running  \n");
        vTaskDelay(pdMS_TO_TICKS(5000));

        printf("Task3 is setting bit TASK_2_BIT\n");

        EventBits_t uxReturn = xEventGroupSync( event_handle,  
                                    TASK_2_BIT,    /* The bit to set. */ 
                                    ALL_SYNC_BITS, /* The bits to wait for. */ 
                                    portMAX_DELAY );/* Timeout value. */
        
        printf("Task3 is syncing\n");


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
    xTaskCreate(Task3, "Task3", 4096, (void*)(intptr_t)3, 1, NULL);
}