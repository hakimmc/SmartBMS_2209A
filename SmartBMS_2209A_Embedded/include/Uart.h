/*
 * Uart.h
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#include "stdint.h"
#include "driver/uart.h"

#define LOG_ENABLE
#ifdef LOG_ENABLE
void LOG(void* pvParameter);
#endif

void Uart_Init(uint8_t uart_pin, uint32_t baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN);
uint8_t Send_Data(uint8_t uart_pin, uint8_t* data, uint8_t data_length);
uint8_t Receive_Data(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout);
uint8_t IsTimeout(uint32_t max_reach_time);

#endif