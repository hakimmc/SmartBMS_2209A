/**
 * @file Uart.c
 * @brief UART initialization, transmission, and reception functions for UART communication.
 * @date 18 December 2024
 * @author hakimmc
 */

#include "LedTaskInit.h"
#include "Uart.h"
#include "Can.h"
#include "Wifi.h"
#include "TcpServer.h"
#include "d2cc_lib.h"
#include "Bq76pl455.h"

/**
 * @brief Initializes the UART peripheral with specified parameters.
 * 
 * This function configures the UART with the specified baud rate, data bits, stop bits, and other settings.
 * It also assigns pins for transmission and reception and installs the UART driver.
 * 
 * @param uart_pin UART port to configure (typically 0, 1, or 2).
 * @param baudrate The baud rate for the UART communication.
 * @param rx_buffsize The size of the receive buffer.
 * @param TXD_PIN The GPIO pin for UART transmission (TX).
 * @param RXD_PIN The GPIO pin for UART reception (RX).
 */
void Uart_Init(uint8_t uart_pin, int baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN)
{
    const uart_config_t uart_config = {
        .baud_rate = baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    esp_err_t ret;

    uart_param_config((uart_port_t)uart_pin, &uart_config); /**< Configures the UART with the given settings. */
    uart_set_pin((uart_port_t)uart_pin, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); /**< Assigns pins to UART. */
    ret = uart_driver_install((uart_port_t)uart_pin, rx_buffsize * 2, 0, 0, NULL, 0); /**< Installs the UART driver with specified buffer size. */
    if (ret != ESP_OK) {
        printf("UART driver installation failed: %s\n", esp_err_to_name(ret));
        return;
    }
}

/**
 * @brief Transmits data via UART.
 * 
 * This function sends a specified amount of data through the UART transmission port.
 * 
 * @param uart_pin UART port to use for transmission (typically 0, 1, or 2).
 * @param data Pointer to the data to be transmitted.
 * @param data_length Length of the data to be transmitted.
 * 
 * @return 1 if transmission is successful, 0 if failed.
 */
uint8_t Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length)
{
    int len = uart_write_bytes((uart_port_t)uart_pin, (const char *)data, data_length); /**< Writes data to UART. */
    if (len < 0) {
        printf("UART transmission failed\n");
        return 0; /**< Transmission failure. */
    }
    return 1; /**< Transmission success. */
}

/**
 * @brief Receives data via UART.
 * 
 * This function receives data from the UART port and stores it in the provided buffer.
 * 
 * @param uart_pin UART port to use for reception (typically 0, 1, or 2).
 * @param data Pointer to the buffer to store received data.
 * @param data_length Length of the data buffer.
 * @param timeout Timeout for receiving data in milliseconds.
 * 
 * @return The number of bytes received or an error code.
 */
int Uart_Receive(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout)
{
    return uart_read_bytes(uart_pin, data, data_length, timeout); /**< Reads data from UART into buffer. */
}

/**
 * @brief Checks if a specified timeout duration has been reached.
 * 
 * This function checks if the specified maximum time has passed since the start of the function call.
 * 
 * @param max_reach_time Maximum time in ticks to wait before timing out.
 * 
 * @return 0 if timeout occurred, 1 if still within the allowed time.
 */
uint8_t IsTimeout(uint32_t max_reach_time)
{
    TickType_t now = xTaskGetTickCount(); /**< Get current tick count. */
    while(xTaskGetTickCount() - now < max_reach_time); /**< Wait for the timeout period to pass. */
    
    if(xTaskGetTickCount() - now >= max_reach_time) {
        return 0; /**< Timeout reached. */
    }
    return 1; /**< Timeout not reached. */
}
