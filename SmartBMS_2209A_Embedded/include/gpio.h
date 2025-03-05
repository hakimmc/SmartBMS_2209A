/**
 * @file gpio.h
 * @brief LED initialization and control tasks for ESP32.
 *
 * This header file provides declarations for initializing GPIO pins and
 * creating LED-related tasks for the ESP32.
 *
 * Created on: 18 Dec 2024
 * @author hakimmc
 */

#ifndef INCLUDE_LEDTASKINIT_H_
#define INCLUDE_LEDTASKINIT_H_

#include "stdint.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/** @brief GPIO pin used for the LED. */
#define LED_PIN 13

/**
 * @brief Initializes a GPIO pin for LED control.
 *
 * Configures the specified GPIO pin as an output to control an LED.
 *
 * @param gpio_pin The GPIO pin number to initialize.
 */
void gpio_init(uint8_t gpio_pin);

/**
 * @brief Task to initialize and control LED behavior.
 *
 * This function serves as an entry point for a FreeRTOS task, handling LED
 * initialization and operation based on the provided parameters.
 *
 * @param pvParameter Pointer to task parameters (optional).
 */
void led_init(void* pvParameter);

#endif /* INCLUDE_LEDTASKINIT_H_ */
