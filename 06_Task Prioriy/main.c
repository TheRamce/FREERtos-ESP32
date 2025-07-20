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
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
typedef struct {
    uint8_t i1;
    uint8_t i2;
} dev;

dev my_dev = {0x01, 0x02};

//=================================================================
void my_function1(void *param)
{

    /*
    //part 1

    dev *p = (dev *)param; // Cast the parameter to the correct type
    printf("parameter 1 is! %d\n", p->i1);
    //printf("parameter 2 is! %d\n", p->i2);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL); // Delete the task itself
    
    */
    while (1)
    {
        /* code */
        printf("Task 1 is running  \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
   


   
}

void my_function2(void *param)
{
    while (1)
    {
        printf("Task 2 is running \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
   

}
//=================================================================

void app_main(void)
{
    /*
    //Part 1: Set and get task priority
    // Create a task with a specific priority and then change its priority

    TaskHandle_t pxTask = NULL;
    xTaskCreate(my_function1, "my_task", 1024, (void *)&my_dev, 24, &pxTask);
    UBaseType_t    t =uxTaskPriorityGet(  pxTask); 
    printf("Before set Task priority is %d\n", t);
    vTaskPrioritySet(  pxTask, 2 ); 
    t = uxTaskPriorityGet( pxTask );
    printf("After set Task priority is %d\n", t);
    
    */

    //part 2: Create multiple tasks with different priorities

    xTaskCreate(my_function1, "my_task", 1024, NULL, 1, NULL);
    xTaskCreate(my_function2, "my_task2", 1024, NULL, 2, NULL);


}
