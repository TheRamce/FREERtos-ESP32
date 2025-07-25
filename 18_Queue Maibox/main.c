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
#include "freertos/queue.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_task_wdt.h"


typedef struct {
    uint8_t message_id;
    uint8_t message[20];
} AMessage;


#define QUEUE_LENGTH 5
#define QUEUE_ITEM_SIZE sizeof(AMessage)

QueueHandle_t my_queue1;

//=================================================================
void message_writer(void *param)
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;

    BaseType_t xpassed;


    int i=1;
    while (1)
    {
       
        xpassed = xQueueOverwrite(my_queue, &i);
        if (xpassed != pdPASS) {
            printf("Failed to send message to queue\n");
        } else {
            printf("Sent: %d\n", i);
        }
        i= (i + 1)%6;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

       
}
//=================================================================
void message_reader1(void *param)   
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;

    BaseType_t xqueue_peek_val; 
    int received_message;
    while (1)
    {

       xqueue_peek_val =xQueuePeek(my_queue, &received_message,  portMAX_DELAY);
        if (xqueue_peek_val == pdPASS) {
            printf("Received: %d\n", received_message);
        } else {
            printf("Failed to receive message from queue\n");
        }
                //to read the data coming from the queue easily, we can use vTaskDelay

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

       
}
//=================================================================
void message_reader2(void *param)   
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;

    BaseType_t xqueue_peek_val; 
    int received_message;
    while (1)
    {

       xqueue_peek_val =xQueuePeek(my_queue, &received_message,  portMAX_DELAY);
        if (xqueue_peek_val == pdPASS) {
            printf("Received: %d\n", received_message);
        } else {
            printf("Failed to receive message from queue\n");
        }
        //to read the data coming from the queue easily, we can use vTaskDelay

        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }


}

//=================================================================
void message_reader3(void *param)   
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;

    BaseType_t xqueue_peek_val; 
    int received_message;
    while (1)
    {

       xqueue_peek_val =xQueuePeek(my_queue, &received_message,  portMAX_DELAY);
        if (xqueue_peek_val == pdPASS) {
            printf("Received: %d\n", received_message);
        } else {
            printf("Failed to receive message from queue\n");
        }
        //to read the data coming from the queue easily, we can use vTaskDelay
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{


    my_queue1 = xQueueCreate(1, sizeof(int));
   

    if (my_queue1 == NULL ) {
        printf("Failed to create queue\n");
        return;
    }
   
    xTaskCreate(message_writer, "message_sender1", 1024*5, (void *)&my_queue1  , 1, NULL);
    xTaskCreate(message_reader1, "message_reader1", 1024*5, (void *)&my_queue1 , 1, NULL);
    xTaskCreate(message_reader2, "message_reader2", 1024*5, (void *)&my_queue1 , 1, NULL);
    xTaskCreate(message_reader3, "message_reader3", 1024*5, (void *)&my_queue1 , 1, NULL);




}
