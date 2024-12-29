/*
 * can.h
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#ifndef INCLUDE_CAN_H_
#define INCLUDE_CAN_H_

#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h"

#define TX_GPIO_NUM             5
#define RX_GPIO_NUM             4

#define CAN_TAG "CAN_MASTER"

#define Can_Main_ID                             0x100
#define Battery_Messages_ID                     0x101
#define Can_Battery_Voltages_ID                 0x102
#define Can_Battery_Temperatures_ID             0x103

#define CAN_DELAY                               250         //ms

uint8_t Can_Init(twai_general_config_t can_gpio_config,twai_timing_config_t can_time_config, twai_filter_config_t can_filter_config);
uint8_t Can_Transmit(twai_message_t message, uint8_t data[]);
void CanReporter(void* pvParameter); //RTOS TASK

#endif /* INCLUDE_CAN_H_ */

