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

//=================================================================
void my_function(void *param)
{
/*
    //first way to create a task and delete it
    //un comment this part to run the first way
    while (1)
    
    {
        printf("Running my_function...\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }


*/
//second way to create a task and delete it             
    {
        printf("Running my_function...1\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
        printf("Running my_function...2\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
        printf("Running my_function...3\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }
    vTaskDelete(NULL); // Delete the task itself

//end of the second way to create a task and delete it
//uncomment the first way to run the first way
}
//=================================================================
void app_main(void)
{
    
    xTaskCreate(my_function, "my_task", 1024, NULL, 1, NULL);

/*
    //works fine, use it with the first way to create a task and delete it
    // Uncomment the following lines to test the first way of creating a task and deleting it
    TaskHandle_t pxCreatedTask = NULL;
    xTaskCreate(my_function, "my_task", 1024, NULL, 1, &pxCreatedTask);


 
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay for 5 seconds
    if (pxCreatedTask!= NULL) 
        vTaskDelete(pxCreatedTask);

*/

    
}
