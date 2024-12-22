/*
 * LedTaskInit.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "LedTaskInit.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN 13

void gpio_init(uint8_t gpio_pin){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    // GPIO SET
    gpio_config(&io_conf);
}

void led_init(void* pvParameter)
{
	int delay_ms = *((int *)pvParameter);
    free(pvParameter);

	gpio_init(LED_PIN);

    while (1)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}
    








