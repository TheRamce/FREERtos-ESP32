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
TaskHandle_t my_task_2 = NULL;

//=================================================================
void my_function1(void *param)
{

    while (1)
    {
        /* code */
        printf("Task 1 is running  \n");
        vTaskDelay(3000 / portTICK_PERIOD_MS);

        vTaskSuspend(my_task_2); // Suspend the second task

        printf("Collect Data 1 \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 30 seconds to allow tasks to run
        printf("Collect Data 2 \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 30 seconds to allow tasks to run
        printf("Collect Data 3 \n");            
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 30 seconds to allow tasks to run
        vTaskResume(my_task_2); // Resume the second task
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
 

    //part 2: Create multiple tasks with different priorities

    xTaskCreate(my_function1, "my_task", 1024, NULL, 1, NULL);
    xTaskCreate(my_function2, "my_task2", 1024, NULL, 1, &my_task_2);  

    static char buffer[1024]={0};

    while (1)
    {
        vTaskList(buffer); // Get the task list
        printf("Task List:\n%s\n", buffer); // Print the task list  
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second to allow tasks to run
        
    }
    

}
