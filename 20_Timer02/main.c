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
#include "freertos/timers.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_task_wdt.h"

void vCallbackFunction( TimerHandle_t  xTimer )
{
    const char *tmrName= pcTimerGetName(  xTimer ); 
    int timerID = (int) pvTimerGetTimerID( xTimer );
    printf("Timer callback called for timer: %s, ID: %d\n", tmrName, timerID);
}

void app_main(void)
{

    TimerHandle_t handle1=NULL,
                  handle2=NULL;
    
    handle1= xTimerCreate( "mytimer",pdMS_TO_TICKS( 1000 ),pdTRUE,  (void *) 0,   vCallbackFunction );
    handle2= xTimerCreate( "mytimer2",pdMS_TO_TICKS( 1000 ),pdTRUE,  (void *) 2,   vCallbackFunction );


    if (handle1 == NULL || handle2 == NULL) {
        printf("Timer creation failed!\n");
    } else {
        printf("Timer created successfully!\n");
    }
    xTimerStart(handle1, 0) ;
    xTimerStart(handle2, 0);   
 



}
