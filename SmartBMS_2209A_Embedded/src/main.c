/*
 * main.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "driver/gpio.h"
#include "LedTaskInit.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main() {

    //LED TASK INIT//
    xTaskCreate(led_init,
                "Toggle",
                256,            // i can change this value. it is testing rn
                500,            // delay toggle
                (UBaseType_t)1, // priority 
                NULL);          // no handle
}