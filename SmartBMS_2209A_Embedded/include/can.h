/**
 * @file Can.h
 * @brief CAN communication interface for ESP32.
 *
 * This header file provides declarations for initializing and managing CAN (Controller Area Network) 
 * communication on the ESP32 using the TWAI (Two-Wire Automotive Interface) driver.
 *
 * Created on: 18 Dec 2024
 * @author hakimmc
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
#include "d2cc_lib.h"

/** 
 * @def TX_GPIO_NUM
 * @brief GPIO pin number for CAN TX.
 */
#define TX_GPIO_NUM             5

/** 
 * @def RX_GPIO_NUM
 * @brief GPIO pin number for CAN RX.
 */
#define RX_GPIO_NUM             4

/** 
 * @def CAN_TAG
 * @brief Tag for logging CAN-related messages.
 */
#define CAN_TAG "CAN_MASTER"

/** 
 * @def CAN_DELAY
 * @brief Delay in milliseconds for CAN tasks.
 */
#define CAN_DELAY                               250 // ms

/**
 * @brief Initializes the CAN interface.
 *
 * Configures the CAN interface with the specified general, timing, and filter configurations.
 *
 * @param can_gpio_config Configuration for CAN GPIO pins.
 * @param can_time_config Timing configuration for CAN communication.
 * @param can_filter_config Filter configuration for CAN messages.
 * @return `0` on success or a non-zero value if initialization fails.
 */
uint8_t Can_Init(twai_general_config_t can_gpio_config, twai_timing_config_t can_time_config, twai_filter_config_t can_filter_config);

/**
 * @brief Transmits a CAN message.
 *
 * Sends a CAN message with the specified data through the CAN interface.
 *
 * @param message The TWAI message structure to transmit.
 * @param data Pointer to the data array to be transmitted.
 * @return `0` on success or a non-zero value if transmission fails.
 */
uint8_t Can_Transmit(twai_message_t message, uint8_t data[]);

/**
 * @brief Task to report CAN messages.
 *
 * A FreeRTOS task that handles CAN communication and reporting.
 *
 * @param pvParameter Pointer to task-specific parameters (optional).
 */
void CanReporter(void* pvParameter);

#endif /* INCLUDE_CAN_H_ */
