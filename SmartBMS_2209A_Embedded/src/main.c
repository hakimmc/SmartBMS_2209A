/*
 * main.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "LedTaskInit.h"
#include "Can.h"
#include "Wifi.h"
#include "TcpServer.h"
#include "d2cc_lib.h"
#include "Bq76pl455.h"


DbcStruct maindbc_struct;

void app_main() {
    printf("\nhelloworld\n");
    nvs_flash_init();	
    Tcp_Init();
    xTaskCreate(CanReporter, "CanTask", 4096,  NULL, (UBaseType_t)2, NULL);
    xTaskCreate(led_init, "ToggleTask", 4096,  NULL, (UBaseType_t)3, NULL);
    xTaskCreate(BQ_Start, "BqTask", 4096,  NULL, (UBaseType_t)4, NULL);
}
