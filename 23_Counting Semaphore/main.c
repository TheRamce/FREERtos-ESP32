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
void carIn(void *param)
{
    UBaseType_t freeParking=0;
    while (1) {
        freeParking=uxSemaphoreGetCount( handle_sem);
        printf("Free parking spots: %d\n", freeParking);
        //1. Resource management.
        // Take the semaphore with a block time of 0, which means it will not block
        //Park your car to the empty parking spot
        // If the semaphore is not available, it will return immediately
        if (xSemaphoreTake( handle_sem, 0 ) == pdTRUE) 
        {
            // Successfully took the semaphore, indicating a parking spot is available
            printf("Car parked successfully!\n");
        } 
        else 
        {
            // No parking spot available
            printf("No parking spots available!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
       
       
    
}

void CarOut(void *param)
{
    while (1) {
        //1. Resource management.
        // Give the semaphore to indicate that a parking spot is now available
        vTaskDelay(pdMS_TO_TICKS(6000)); // Delay for 6000 ms
        if (xSemaphoreGive(handle_sem) == pdTRUE) {
            printf("Car left, parking spot is now available!\n");
        } else {
            printf("Failed to release parking spot!\n");
        }
    }

}


void app_main(void)
{
    //2. Resource management. 
    // Create a counting semaphore with an initial count of 5 and a maximum count of 5
    handle_sem=xSemaphoreCreateCounting(5,5); 
    if (handle_sem == NULL) {
        printf("Failed to create semaphore\n");
        return; 
    }

    xTaskCreate(carIn, "Task1", 1024*4, NULL, 5, NULL);
    xTaskCreate(CarOut, "Task2", 1024*4, NULL, 5, NULL);
}
