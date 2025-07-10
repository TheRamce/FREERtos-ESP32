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
void my_function(void *param)
{

    dev *p = (dev *)param; // Cast the parameter to the correct type

    printf("parameter 1 is! %d\n", p->i1);
    printf("parameter 2 is! %d\n", p->i2);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL); // Delete the task itself
}
//=================================================================

void app_main(void)
{
    int test = 10;
    
    xTaskCreate(my_function, "my_task", 1024, (void *)&my_dev, 1, NULL);

}
