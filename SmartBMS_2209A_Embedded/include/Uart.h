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

//#define LOG_ENABLE
#ifdef LOG_ENABLE
void LOG_Init(uint8_t uart_pin);
void LOG(uint8_t uart_pin, uint8_t data_length);
#endif

void Uart_Init(uint8_t uart_pin);
void Send_Data(uint8_t uart_pin, uint8_t data_length);

#endif