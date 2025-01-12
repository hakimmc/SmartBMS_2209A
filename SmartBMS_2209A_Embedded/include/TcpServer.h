/*
 * TcpServer.h
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#ifndef INCLUDE_TCPSERVER_H_
#define INCLUDE_TCPSERVER_H_

/* if you need to use wifi connect just uncomment WIFI_CONNECT */

//#define WIFI_CONNECT

#include <lwip/sockets.h>
#include <esp_log.h>
#include <string.h>
#include <errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "Wifi.h"
#include "string.h"
#include "esp_ping.h"
#include "ping/ping_sock.h"
#include "nvs_flash.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "d2cc_lib.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define TCP_TAG         "TCP_SERVER"
#define SERVER_PORT     5166



void Handle_Client(void* args);
void Create_Server(void* pvParameter);
int receive_data(int sock, char* buffer, size_t size, uint8_t* timeout_counter, uint8_t max_timeout);
void Tcp_Init();

#endif /* INCLUDE_TCPSERVER_H_ */
