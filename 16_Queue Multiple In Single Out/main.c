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
void message_sender1(void *param)
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;

    int i=1;
    while (1)
    {
       
        
        if (xQueueSendToBack(my_queue, &i, 0) != pdPASS) {
            printf("Failed to send message to queue\n");
        } else {
            printf("Sent: %d\n", i);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

       
}


void message_sender2(void *param)
{

    QueueHandle_t my_queue = *(QueueHandle_t *)param;

    int j=2;
    while (1)
    {
       
        
        if (xQueueSendToBack(my_queue, &j, 0) != pdPASS) {
            printf("Failed to send message to queue\n");
        } else {
            printf("Sent: %d\n", j);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

       
}

void message_receiver(void *param)
{
    QueueHandle_t my_queue = *(QueueHandle_t *)param;
    int received_message;

    while (1)
    {

        //PORTMAX DELAY WILL HELP US TO DELAY THE RECEIVER TASK UNTIL A MESSAGE IS AVAILABLE
        //IF WE USE 0, IT WILL RETURN IMMEDIATELY IF NO MESSAGE
        if (xQueueReceive(my_queue, &received_message, portMAX_DELAY) == pdPASS) {
            printf("Received: %d\n", received_message);
        } else {
            printf("Failed to receive message from queue\n");
        }
        
    }

}

//=================================================================

void app_main(void)
{
    QueueHandle_t my_queue ;

    my_queue=xQueueCreate(QUEUE_LENGTH, sizeof(int));

    if (my_queue == NULL) {
        printf("Failed to create queue\n");
        return;
    }
    
    xTaskCreate(message_sender1, "message_sender1", 1024*5, (void *)&my_queue , 1, NULL);
    xTaskCreate(message_sender2, "message_sender", 1024*5, (void *)&my_queue , 1, NULL);
    //BEACUSE OF THE PRIORITY, THE RECEIVER TASK WILL BE EXECUTED FIRST
    xTaskCreate(message_receiver, "message_receiver", 1024*5, (void *)&my_queue, 2, NULL);


}
