/**
 * @file Bq76pl455.c
 * @brief Implementation file for interfacing with the BQ76PL455A-Q1 battery management IC.
 *
 * Provides functionality to initialize, communicate, and calculate CRC for the BQ76PL455A-Q1 IC.
 *
 * Created on: 18 Dec 2024
 * @author 
 */

#include "Bq76pl455.h"

/* ----------------- CRC Table ----------------- */
const uint16_t crc16_table_bq[256] = {
    // Precomputed CRC-16 table
    // 0x0000 - 0xFFFF
    /* Add your CRC table here */
};

/**
 * @brief Initialize the BQ76PL455A-Q1 communication interface.
 *
 * Configures the UART for the BQ76PL455A-Q1.
 */
void BQ_Init() {
    Uart_Init(BQ_UART_PORT, 250000, 8, BQ_TX, BQ_RX);
}

/**
 * @brief Test communication with the BQ76PL455A-Q1 device.
 *
 * Sends a test message to read the device ID.
 */
void BQ_Test() {
    uint8_t Read_Id_Message[] = {0x89, 0x01, 0x00, 0x0A, 0x00, 0xDA, 0x83};
    Uart_Transmit(BQ_UART_PORT, Read_Id_Message, 7);
    // Further response handling logic can be implemented here.
}

/**
 * @brief Starts the main task for BQ76PL455A-Q1.
 *
 * Continuously transmits a test message via UART at regular intervals.
 *
 * @param args Task-specific arguments (optional).
 */
void BQ_Start(void *args) {
    BQ_Uart_Init(BQ_UART_PORT, 250000, 256, BQ_TX, BQ_RX);

    //uint8_t data[] = {'h', 'e', 'l', 'o'};
    uint8_t data[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    while (1) {
        if (BQ_Uart_Transmit(BQ_UART_PORT, data, sizeof(data))) {
            printf("Data sent\n");
        } else {
            printf("Data send failed\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Calculate the CRC-16 checksum for a given data buffer.
 *
 * @param data Pointer to the data buffer.
 * @param data_length Length of the data buffer in bytes.
 * @return Pointer to a 2-byte array containing the CRC checksum.
 */
uint8_t* CRC16(uint8_t* data, uint8_t data_length) {
    static uint8_t out_data[2];
    uint16_t CRC = 0;

    for (int i = 0; i < data_length; i++) {
        CRC ^= (*data++) & 0x00FF;
        CRC = crc16_table_bq[CRC & 0x00FF] ^ (CRC >> 8);
    }

    out_data[0] = (uint8_t)((CRC >> 8) & 0xFF); // MSB
    out_data[1] = (uint8_t)(CRC & 0xFF);       // LSB
    return out_data;
}

/**
 * @brief Initialize UART for communication with the BQ76PL455A-Q1.
 *
 * @param uart_pin UART port number.
 * @param baudrate Baud rate for UART communication.
 * @param rx_buffsize RX buffer size.
 * @param TXD_PIN GPIO pin for UART TX.
 * @param RXD_PIN GPIO pin for UART RX.
 */
void BQ_Uart_Init(uint8_t uart_pin, int baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN) {
    const uart_config_t uart_config = {
        .baud_rate = baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    esp_err_t ret = uart_param_config((uart_port_t)uart_pin, &uart_config);
    if (ret != ESP_OK) {
        printf("UART parameter configuration failed: %s\n", esp_err_to_name(ret));
        return;
    }

    ret = uart_set_pin((uart_port_t)uart_pin, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if (ret != ESP_OK) {
        printf("UART pin assignment failed: %s\n", esp_err_to_name(ret));
        return;
    }

    ret = uart_driver_install((uart_port_t)uart_pin, rx_buffsize * 2, 0, 0, NULL, 0);
    if (ret != ESP_OK) {
        printf("UART driver installation failed: %s\n", esp_err_to_name(ret));
    }
}

/**
 * @brief Transmit data via UART to the BQ76PL455A-Q1.
 *
 * @param uart_pin UART port number.
 * @param data Pointer to the data buffer to be transmitted.
 * @param data_length Length of the data buffer in bytes.
 * @return 1 on success, 0 on failure.
 */
uint8_t BQ_Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length) {
    int len = uart_write_bytes((uart_port_t)uart_pin, (const char *)data, data_length);
    if (len < 0) {
        printf("UART transmission failed\n");
        return 0;
    }
    return 1;
}
