/*
 * Uart.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "stdint.h"
#include "Uart.h"


void LOG(void* pvParameter){
    printf("logging\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void Uart_Init(uint8_t uart_pin, uint32_t baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN){
    const uart_config_t uart_config = {
        .baud_rate = baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install((uart_port_t)uart_pin, rx_buffsize * 2, 0, 0, NULL, 0);
    uart_param_config((uart_port_t)uart_pin, &uart_config);
    uart_set_pin((uart_port_t)uart_pin, TXD_PIN , RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
uint8_t Send_Data(uint8_t uart_pin, uint8_t* data, uint8_t data_length){
    uart_write_bytes((uart_port_t)uart_pin, data, data_length);
    return 1;
}

uint8_t Receive_Data(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout){
    while(uart_read_bytes(uart_pin, data, data_length, 1000)<=0 && timeout--);
    if(!timeout){return 0;}
    return 1;

}

uint8_t IsTimeout(uint32_t max_reach_time){
    TickType_t now = xTaskGetTickCount;
    while(xTaskGetTickCount-now<max_reach_time);
    return 1;
}