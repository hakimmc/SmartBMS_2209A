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
#include "Uart.h"

void app_main() {

    //LED TASK INIT//
    //Uart_Init(UART_NUM_1,115200,128*2,GPIO_NUM_43,GPIO_NUM_42);
    printf("\nhelloworld\n");

    xTaskCreate(led_init,
                "Toggle",
                4095,            // i can change this value. it is testing rn
                NULL,            // delay toggle
                (UBaseType_t)1, // priority 
                NULL);          // no handle
    xTaskCreate(LOG,
                "log",
                4095,            // i can change this value. it is testing rn
                NULL,            // log text
                (UBaseType_t)2, // priority 
                NULL);          // no handle
}