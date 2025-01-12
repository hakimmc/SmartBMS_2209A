/*
 * Bq76pl455.h
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

/* Message Format V

[Broadcast Command Hex Code (1Byte)] [Register Address (1Byte)] [Data (2Byte)] [CRC (2Byte)]

About CRC Calculation From Datasheet :

89 01 00 0A 00 DA 83 This message reads the bq76PL455A-Q1 Device Address register.

• Data bytes sent from a bq76PL455A-Q1 device back to the host are shown as a series of hexadecimal numbeN ÇNÖÇÇÖNÇLPÖesponse) This response to the prior example message means, Device Address = 1.

The CRC in the message is a standard CRC-16 IBM, but with the most significant bit (MSB) and least
significant bit (LSB) stored in reverse order. Specifically in the previous sample message, a standard
calculation would yield a CRC-16 of 83DA, but it is stored in the message as DA83. Standard calculators
are available online for verification of cyclic redundancy checks (CRCs). 

*/

#include "Uart.h"

#define BQ_UART_PORT    UART_NUM_1
#define BQ_TX           12 
#define BQ_RX           11 
 
 
void Bq_Init();
void BQ_Test();
uint8_t* CRC16(uint8_t* data, uint8_t data_length);
void BQ_Start(void *args);
void BQ_Uart_Init(uint8_t uart_pin, int baudrate, uint32_t rx_buffsize, uint8_t TXD_PIN, uint8_t RXD_PIN) ;
uint8_t BQ_Uart_Transmit(uint8_t uart_pin, uint8_t *data, uint8_t data_length) ;

