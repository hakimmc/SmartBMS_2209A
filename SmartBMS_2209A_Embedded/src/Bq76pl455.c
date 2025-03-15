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

/**
 * @brief Starts the main task for BQ76PL455A-Q1.
 *
 * Continuously transmits a test message via UART at regular intervals.
 *
 * @param args Task-specific arguments (optional).
 */
void BQ_Start(void *args) {
    /** @brief BQ76PL455 Uart Init (250k baud) */
    BQ_Uart_Init(BQ_UART_PORT, 250000, 256, BQ_TX, BQ_RX);
    gpio_init(BQ_WAKEUP);
    BQ_ShutDown();
    vTaskDelay(pdMS_TO_TICKS(10));
    BQ_WakeUp();
    //uint8_t Dev_Addr = BQ_Read_DevAddr_Reg();
    //printf("BQ Dev Address : %d");
    //uint8_t data[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    uint8_t data[] = {'H','E','L','L','O'};
    while (1) {
        if (BQ_Uart_Transmit(BQ_UART_PORT, data, sizeof(data))) {
            printf("Data sent\n");
            if(BQ_Uart_Receive(BQ_UART_PORT, data, 5, 1000)) printf("Data received\n");
        } else {
            printf("Data send failed\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/* ----------------- CRC Table ----------------- */
const uint16_t crc16_table_bq[256] = { // CRC16 polynomial: x^16 + x^15 + x^2 + 1
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
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
 * @brief Read Device Address Register of BQ76PL455A-Q1 device.
 */
uint8_t BQ_Read_DevAddr_Reg() {
    uint8_t Read_Id_Message[] = {0x89, 0x01, 0x00, 0x0A, 0x00, 0xDA, 0x83};
    Uart_Transmit(BQ_UART_PORT, Read_Id_Message, 7);
    uint8_t rx_data[4];
    while(BQ_Uart_Receive(BQ_UART_PORT,rx_data,4,1000) && Check_CRC16(rx_data,4) != true);
    return rx_data[1];
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
    /** @brief crc control bytes */
    out_data[0] = (uint8_t)(CRC & 0xFF);       // LSB
    out_data[1] = (uint8_t)((CRC >> 8) & 0xFF); // MSB
    return out_data;
}

/**
 * @brief Checking the CRC-16 for a given data buffer.
 * @param data Pointer to the data buffer for which the CRC needs to be calculated.
 * @param data_length The length of the data buffer in bytes (all byte length).
 * @return true if CRC is same with datas last 2 index, else it is false.
 */
bool Check_CRC16(uint8_t* data, uint8_t data_length){
    uint8_t* crc_data = CRC16(data,data_length-2);
    if(*crc_data != data[data_length-2]) return false;
    if(*(crc_data+1) != data[data_length-1]) return false;
    return true;
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
 * @brief Uninitialize UART for communication with the BQ76PL455A-Q1.
 *
 * @param uart_pin UART port number.
 */
void BQ_Uart_Deinit(uint8_t uart_pin) {
    uart_driver_delete(uart_pin);
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

/**
 * @brief Create tx message array for BQ76PL455 with command
 * @param CMD Command Number

void BQ_Create_Tx_Table(BQ_Command_TX CMD, uint8_t* Bq_Data, uint8_t Length){
    switch (CMD)
    {
        case 1:
            break;
        
        case 2:
            break;
    }
}*/

/**
 * @brief Waking up BQ76PL455A-Q1.
 */
void BQ_WakeUp(){
    gpio_set_level(BQ_WAKEUP, 1);
}

/**
 * @brief Shutdown BQ76PL455A-Q1.
 */
void BQ_ShutDown(){
    gpio_set_level(BQ_WAKEUP, 0);
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
int BQ_Uart_Receive(uint8_t uart_pin, uint8_t* data, uint8_t data_length, uint32_t timeout)
{
    return uart_read_bytes(uart_pin, data, data_length, pdMS_TO_TICKS(timeout)) == ESP_OK ? 1 : 0; /**< Reads data from UART into buffer. */
}