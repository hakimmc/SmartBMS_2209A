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

#include "stdbool.h"
#include "Uart.h"
#include "gpio.h"

/**W
 * @brief CMD enum table
 */

typedef enum{
    Single_Dev_Write_W_Resp_1B = 0x81,
    Single_Dev_Write_Wout_Resp_2B = 0x92,
    BroadCast_Write_Wout_Resp_1B = 0xF1,
    BroadCast_Write_Wout_Resp_2B
}BQ_Command_TX;

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
 * @def BQ_WAKEUP
 * @brief GPIO pin for waking up BQ76PL455A-Q1.
 */
#define BQ_WAKEUP           47

/**
 * @def BQ_WAKEUP
 * @brief GPIO pin for catch fault of BQ76PL455A-Q1.
 */
#define BQ_FAULT            21

/**
 * @brief Initializes the BQ76PL455A-Q1 interface.
 *
 * Sets up the UART interface and any necessary configurations for communication with
 * the BQ76PL455A-Q1 device.
 */
void Bq_Init();

/**
 * @brief Read Device Address Register of BQ76PL455A-Q1 device.
 */
uint8_t BQ_Read_DevAddr_Reg();

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
 * @brief Checking the CRC-16 for a given data buffer.
 * @param data Pointer to the data buffer for which the CRC needs to be calculated.
 * @param data_length The length of the data buffer in bytes (all byte length).
 * @return true if CRC is same with datas last 2 index, else it is false.
 */
bool Check_CRC16(uint8_t* data, uint8_t data_length);

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

/**
 * @brief Create tx message array for BQ76PL455 with command
 * @param CMD Command Number
 */
 void BQ_Create_Tx_Table(BQ_Command_TX CMD, uint8_t* Bq_Data, uint8_t Length);

/**
 * @brief Waking up BQ76PL455A-Q1.
 */
void BQ_WakeUp();

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
int BQ_Uart_Receive(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout);

#endif /* BQ76PL455_H_ */
