/**
 * @file Bq76pl455.h
 * @brief Header file for interfacing with the BQ76PL455A-Q1 battery management IC.
 *
 * This file provides declarations for initializing, communicating, and managing the 
 * BQ76PL455A-Q1 IC using UART. It includes CRC-16 calculation and message structure details.
 *
 * Created on: 18 Dec 2024
 * @author hakimmc
 */

#ifndef BQ76PL455_H_
#define BQ76PL455_H_

#include "Uart.h"

/**
 * @def BQ_UART_PORT
 * @brief UART port used for communication with the BQ76PL455A-Q1.
 */
#define BQ_UART_PORT    UART_NUM_1

/**
 * @def BQ_TX
 * @brief GPIO pin number for UART TX (transmit) connected to the BQ76PL455A-Q1.
 */
#define BQ_TX           12

/**
 * @def BQ_RX
 * @brief GPIO pin number for UART RX (receive) connected to the BQ76PL455A-Q1.
 */
#define BQ_RX           11

/**
 * @brief Initializes the BQ76PL455A-Q1 interface.
 *
 * Sets up the UART interface and any necessary configurations for communication with
 * the BQ76PL455A-Q1 device.
 */
void Bq_Init();

/**
 * @brief Tests the communication with the BQ76PL455A-Q1.
 *
 * Sends a test command or sequence to verify the functionality of the BQ76PL455A-Q1.
 */
void BQ_Test();

/**
 * @brief Calculates the CRC-16 for a given data buffer.
 *
 * Computes the CRC-16 using the IBM standard with reversed MSB and LSB for
 * compatibility with the BQ76PL455A-Q1 message format.
 *
 * @param data Pointer to the data buffer for which the CRC needs to be calculated.
 * @param data_length The length of the data buffer in bytes.
 * @return Pointer to a 2-byte array containing the CRC-16 result.
 */
uint8_t* CRC16(uint8_t* data, uint8_t data_length);

/**
 * @brief Starts the BQ76PL455A-Q1 task.
 *
 * A FreeRTOS task responsible for managing communication with the BQ76PL455A-Q1.
 *
 * @param args Pointer to task-specific arguments (optional).
 */
void BQ_Start(void *args);

/**
 * @brief Initializes the UART interface for the BQ76PL455A-Q1.
 *
 * Configures the UART parameters for communicating with the BQ76PL455A-Q1, including
 * pin assignments, baud rate, and RX buffer size.
 *
 * @param uart_pin The UART port number to initialize.
 * @param baudrate The desired baud rate for communication.
 * @param rx_buffsize The size of the RX buffer.
 * @param TXD_PIN The GPIO pin number for UART TX.
 * @param RXD_PIN The GPIO pin number for UART RX.
 */
void BQ_Uart_Init(uint8_t uart_pin, int baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN);

/**
 * @brief Transmits data to the BQ76PL455A-Q1 over UART.
 *
 * Sends a sequence of bytes to the BQ76PL455A-Q1 via UART.
 *
 * @param uart_pin The UART port number to use for transmission.
 * @param data Pointer to the data buffer to be transmitted.
 * @param data_length The length of the data buffer in bytes.
 * @return Returns `0` on success or a non-zero value on failure.
 */
uint8_t BQ_Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length);

#endif /* BQ76PL455_H_ */
