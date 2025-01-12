/*
 * Uart.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "LedTaskInit.h"
#include "Uart.h"
#include "Can.h"
#include "Wifi.h"
#include "TcpServer.h"
#include "d2cc_lib.h"
#include "Bq76pl455.h"


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

    uart_param_config((uart_port_t)uart_pin, &uart_config);
    uart_set_pin((uart_port_t)uart_pin, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    ret = uart_driver_install((uart_port_t)uart_pin, rx_buffsize * 2, 0, 0, NULL, 0);
    if (ret != ESP_OK) {
        printf("UART driver installation failed: %s\n", esp_err_to_name(ret));
        return;
    }
}

uint8_t Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length) 
{
    int len = uart_write_bytes((uart_port_t)uart_pin, (const char *)data, data_length);
    if (len < 0) {
        printf("UART transmission failed\n");
        return 0;
    }
    return 1;
}

int Uart_Receive(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout)
{
    return uart_read_bytes(uart_pin, data, data_length, timeout);
}

uint8_t IsTimeout(uint32_t max_reach_time)
{
    // 0 timeout; 1 Ok;
    TickType_t now = xTaskGetTickCount();
    while(xTaskGetTickCount()-now<max_reach_time);
    if(xTaskGetTickCount()-now>=max_reach_time){
        return 0;
    }
    return 1;
}