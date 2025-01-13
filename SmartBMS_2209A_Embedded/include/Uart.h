/**
 * @file Uart.h
 * @brief UART driver interface for ESP32.
 *
 * This header file provides the function declarations for initializing and 
 * using UART communication on the ESP32.
 *
 * Created on: 18 Dec 2024
 * @author hakimmc
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#include "stdint.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initializes the UART interface.
 *
 * Configures the UART interface with the specified parameters, including pin assignments,
 * baud rate, and RX buffer size.
 *
 * @param uart_pin The UART port number to initialize (e.g., UART_NUM_0, UART_NUM_1).
 * @param baudrate The desired baud rate for communication.
 * @param rx_buffsize The size of the RX buffer.
 * @param TXD_PIN The GPIO pin number assigned for UART TX (transmit).
 * @param RXD_PIN The GPIO pin number assigned for UART RX (receive).
 */
void Uart_Init(uint8_t uart_pin, int baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN);

/**
 * @brief Transmits data over UART.
 *
 * Sends a sequence of bytes through the specified UART port.
 *
 * @param uart_pin The UART port number to use for transmission.
 * @param data Pointer to the data buffer containing the bytes to transmit.
 * @param data_length The number of bytes to transmit.
 * @return Returns `0` on success or a non-zero value if the transmission fails.
 */
uint8_t Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length);

/**
 * @brief Receives data from UART.
 *
 * Reads data from the specified UART port into a buffer, with an optional timeout.
 *
 * @param uart_pin The UART port number to use for reception.
 * @param data Pointer to the buffer where received data will be stored.
 * @param data_length The maximum number of bytes to read.
 * @param timeout The maximum time to wait for data in milliseconds.
 * @return The number of bytes successfully received, or a negative value on error.
 */
int Uart_Receive(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout);

/**
 * @brief Checks for a timeout condition.
 *
 * Determines if a given time has exceeded the specified maximum time limit.
 *
 * @param max_reach_time The maximum allowable time in milliseconds.
 * @return Returns `1` if the timeout condition is met, or `0` otherwise.
 */
uint8_t IsTimeout(uint32_t max_reach_time);

#endif // INCLUDE_UART_H_
