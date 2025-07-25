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

SemaphoreHandle_t handle_mutex=NULL;
void Task1(void *param)
{

    UBaseType_t prio=uxTaskPriorityGet( NULL ); 
    printf("Task1 enter priority: %d\n", prio);


    while (1) {

        xSemaphoreTake(handle_mutex, portMAX_DELAY); // Wait indefinitely for the semaphore
        prio=uxTaskPriorityGet( NULL ); 
        printf("Task1 inside critical section priority: %d\n", prio);

        for (size_t i = 0; i < 5; i++)
        {
            prio=uxTaskPriorityGet( NULL ); 
            printf("Task1 is running, iteration: %zu  and prio: %d\n", i, prio);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
        }
        xSemaphoreGive(handle_mutex); // Release the semaphore
    }  
    
}

void Task2(void *param)
{
    while (1) {
        //1. Resource management.
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
        UBaseType_t prio=uxTaskPriorityGet( NULL );
        printf("Task2 is running, current priority: %d\n", prio);
        xSemaphoreTake(handle_mutex, portMAX_DELAY); // Wait indefinitely for the semaphore

        for (size_t i = 0; i < 5; i++)
        {
            prio=uxTaskPriorityGet( NULL );
            printf("Task2 is running, iteration: %zu  and prio: %d\n", i, prio);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
        }
        xSemaphoreGive(handle_mutex); // Release the semaphore
        

    }

}


void app_main(void)
{
    //2. Resource management. 
    // Create a counting semaphore with an initial count of 5 and a maximum count of 5
    handle_mutex=xSemaphoreCreateMutex(); 
    if (handle_mutex == NULL) {
        printf("Failed to create semaphore\n");
        return; 
    }

    xTaskCreate(Task1, "Task1", 1024*4, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 1024*4, NULL, 2, NULL);
}
