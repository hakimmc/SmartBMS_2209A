/**
 * @file gpio.c
 * @brief Implementation of LED blinking task using ESP32 GPIO.
 * @date 18 December 2024
 * @author hakimmc
 */

#include "gpio.h"

/**
 * @brief Initializes the specified GPIO pin as an output.
 * 
 * This function configures the given GPIO pin for output mode with no pull-up or pull-down resistors.
 * 
 * @param gpio_pin The GPIO pin number to initialize.
 */
void gpio_init(uint8_t gpio_pin)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;        /**< No interrupt triggered. */
    io_conf.mode = GPIO_MODE_OUTPUT;             /**< Set GPIO mode to output. */
    io_conf.pin_bit_mask = (1ULL << gpio_pin);   /**< Pin mask for the specified GPIO pin. */
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; /**< Disable pull-down resistor. */
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;     /**< Disable pull-up resistor. */
    
    // Configure the GPIO
    gpio_config(&io_conf);
}

/**
 * @brief LED blinking task.
 * 
 * This task initializes the LED GPIO pin and continuously toggles the LED state with a 500 ms delay.
 * 
 * @param pvParameter A pointer to task-specific parameters (unused).
 */
void led_init(void* pvParameter)
{
    gpio_init(LED_PIN); /**< Initialize the LED GPIO pin. */
    while (1)
    {
        gpio_set_level(LED_PIN, 1); /**< Turn the LED on. */
        vTaskDelay(pdMS_TO_TICKS(500)); /**< Delay for 500 ms. */
        gpio_set_level(LED_PIN, 0); /**< Turn the LED off. */
        vTaskDelay(pdMS_TO_TICKS(500)); /**< Delay for 500 ms. */
    }
}
