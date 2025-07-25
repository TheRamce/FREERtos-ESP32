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

QueueSetHandle_t my_queue_set;
QueueHandle_t my_queue1, my_queue2;

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
    QueueSetHandle_t my_queue = *(QueueSetHandle_t *)param;
    int received_message;
    QueueSetMemberHandle_t xQueueMember;

    while (1)
    {

        //PORTMAX DELAY WILL HELP US TO DELAY THE RECEIVER TASK UNTIL A MESSAGE IS AVAILABLE
        //IF WE USE 0, IT WILL RETURN IMMEDIATELY IF NO MESSAGE
        xQueueMember = xQueueSelectFromSet(my_queue, portMAX_DELAY);

        if(xQueueMember==my_queue1)
        {
            printf("Received from queue 1\n");
            
        }
        else if(xQueueMember==my_queue2)
        {
            printf("Received from queue 2\n");
        }
        else
        {
            printf("Received from unknown queue\n");
            continue; // Skip to the next iteration if the queue is not recognized
        }
        if (xQueueReceive(xQueueMember, &received_message, 0) == pdPASS) {
            printf("Received: %d\n", received_message);
        } else {
            printf("Failed to receive message from queue\n");
        }
        
    }

}

//=================================================================

void app_main(void)
{


    my_queue1 = xQueueCreate(QUEUE_LENGTH, sizeof(int));
    my_queue2 = xQueueCreate(QUEUE_LENGTH, sizeof(int));

    my_queue_set = xQueueCreateSet( QUEUE_LENGTH*2 ); 


    if (my_queue1 == NULL || my_queue2 == NULL || my_queue_set == NULL) {
        printf("Failed to create queue\n");
        return;
    }
    xQueueAddToSet(my_queue1, my_queue_set);
    xQueueAddToSet(my_queue2, my_queue_set);
    
    xTaskCreate(message_sender1, "message_sender1", 1024*5, (void *)&my_queue1 , 1, NULL);
    xTaskCreate(message_sender2, "message_sender2", 1024*5, (void *)&my_queue2 , 1, NULL);
    //BEACUSE OF THE PRIORITY, THE RECEIVER TASK WILL BE EXECUTED FIRST
    xTaskCreate(message_receiver, "message_receiver", 1024*5, (void *)&my_queue_set, 2, NULL);


}
