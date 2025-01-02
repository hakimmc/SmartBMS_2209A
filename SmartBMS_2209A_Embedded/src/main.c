/*
 * main.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "LedTaskInit.h"
#include "Uart.h"
#include "Can.h"
#include "Wifi.h"
#include "TcpServer.h"
#include "husarnet.h"

void app_main() {
    printf("\nhelloworld\n");
    nvs_flash_init();	
    Tcp_Init();
    husarnet_join();
    xTaskCreate(CanReporter, "CanTask", 4096,  NULL, (UBaseType_t)2, NULL);
    xTaskCreate(led_init, "ToggleTask", 4096,  NULL, (UBaseType_t)3, NULL);
}
