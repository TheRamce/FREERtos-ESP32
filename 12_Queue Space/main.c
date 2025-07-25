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

//=================================================================
void message_sender(void *param)
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;
    AMessage my_dev;    
    my_dev.message_id = 0;
    

    while (1)
    {
        UBaseType_t q_free_size= uxQueueSpacesAvailable( my_queue ); 
        printf("Queue free size: %d\n", q_free_size);
        my_dev.message_id++;
        snprintf((char *)my_dev.message, sizeof(my_dev.message), "Message %d", my_dev.message_id);
        
        if (xQueueSendToBack(my_queue, &my_dev, 0) != pdPASS) {
            printf("Failed to send message to queue\n");
        } else {
            printf("Sent: %s\n", my_dev.message);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

       
}

void message_receiver(void *param)
{
    QueueHandle_t my_queue = *(QueueHandle_t *)param;
    // AMessage received_message;

    while (1)
    {
        UBaseType_t wait_value=uxQueueMessagesWaiting( my_queue ); 
        printf("Queue waiting messages: %d\n", wait_value);

        // if (xQueueReceive(my_queue, &received_message, 0) == pdPASS) {
        //     printf("Received: %s\n", received_message.message);
        // } else {
        //     printf("Failed to receive message from queue\n");
        // }
        
        vTaskDelay(pdMS_TO_TICKS(1000));        
    }

}

//=================================================================

void app_main(void)
{
    QueueHandle_t my_queue ;
    
    my_queue=xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);

    if (my_queue == NULL) {
        printf("Failed to create queue\n");
        return;
    }
    
    xTaskCreate(message_sender, "message_sender", 1024*5, (void *)&my_queue , 5, NULL);
    xTaskCreate(message_receiver, "message_receiver", 1024*5, (void *)&my_queue, 5, NULL);


}
