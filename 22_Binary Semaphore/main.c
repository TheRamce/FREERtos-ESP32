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

SemaphoreHandle_t handle_sem=NULL;
void task_function1(void *param)
{
    while (1) {

        xSemaphoreTake( handle_sem, portMAX_DELAY ); 
        for (size_t i = 0; i < 5; i++)
        {
            printf("Hello from task1! %d\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
        }
        xSemaphoreGive( handle_sem );
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
       
    }
}

void task_function2(void *param)
{
    while (1) {

        xSemaphoreTake( handle_sem, portMAX_DELAY ); 
        for (size_t i = 0; i < 5; i++)
        {
            printf("Hello from task2! %d\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
        }
        xSemaphoreGive( handle_sem );
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
       
    }
}


void app_main(void)
{

    handle_sem=xSemaphoreCreateBinary(  ); 
    if (handle_sem == NULL) {
        printf("Failed to create semaphore\n");
        return; 
    }
    //first give the semaphore
    xSemaphoreGive( handle_sem ); 

    // Create a task
    xTaskCreate(task_function1, "Task1", 1024*4, NULL, 5, NULL);
    xTaskCreate(task_function2, "Task2", 1024*4, NULL, 5, NULL);
}
