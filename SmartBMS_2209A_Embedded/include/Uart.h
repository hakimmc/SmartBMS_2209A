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
#include "driver/gpio.h"
#include <stdio.h>
#include <stdlib.h>


void Uart_Init(uint8_t uart_pin, int baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN) ;
uint8_t Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length) ;
int Uart_Receive(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout);
uint8_t IsTimeout(uint32_t max_reach_time);

#endif