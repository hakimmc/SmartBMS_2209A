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
#include "can.h"

void app_main() {
    printf("\nhelloworld\n");
    xTaskCreate(CanReporter, "CanTask", 4096,  NULL, (UBaseType_t)1, NULL);
    xTaskCreate(led_init, "ToggleTask", 4096,  NULL, (UBaseType_t)2, NULL);
}
