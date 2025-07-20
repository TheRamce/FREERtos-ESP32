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
       // printf("Task 1 is running  \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
       
}

//=================================================================

void app_main(void)
{
 

    //part 2: Create multiple tasks with different priorities
    TaskHandle_t my_task_1 = NULL;
    xTaskCreate(my_function1, "my_task1", 1024, NULL, 1, &my_task_1);

    UBaseType_t x=0;

    while (1)
    {

      x= uxTaskGetStackHighWaterMark2(my_task_1 );
      printf("High water mark for my_dev.i1: %u\n", x);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    

}
