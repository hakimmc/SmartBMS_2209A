/**
 * @file TcpServer.h
 * @brief TCP server implementation for ESP32.
 *
 * This header file provides declarations for functions and macros used in 
 * implementing a TCP server on the ESP32. It supports handling client connections 
 * and data transfer over Wi-Fi.
 *
 * Created on: 18 Dec 2024
 * @author hakimmc
 */

#ifndef INCLUDE_TCPSERVER_H_
#define INCLUDE_TCPSERVER_H_

/** 
 * @brief Uncomment the following line to enable Wi-Fi connection functionality.
 */
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

/** 
 * @def WIFI_CONNECTED_BIT
 * @brief Event bit indicating a successful Wi-Fi connection.
 */
#define WIFI_CONNECTED_BIT BIT0

/** 
 * @def WIFI_FAIL_BIT
 * @brief Event bit indicating a Wi-Fi connection failure.
 */
#define WIFI_FAIL_BIT      BIT1

/** 
 * @def TCP_TAG
 * @brief Tag for logging TCP server messages.
 */
#define TCP_TAG         "TCP_SERVER"

/** 
 * @def SERVER_PORT
 * @brief Port number for the TCP server.
 */
#define SERVER_PORT     5166

/**
 * @brief Handles client connections to the TCP server.
 *
 * This function processes communication with a connected client, handling data
 * transmission and reception as required.
 *
 * @param args Pointer to additional arguments (optional).
 */
void Handle_Client(void* args);

/**
 * @brief Creates and starts the TCP server.
 *
 * Sets up the TCP server to listen for incoming client connections and handle them
 * using the specified parameters.
 *
 * @param pvParameter Pointer to additional parameters for server setup (optional).
 */
void Create_Server(void* pvParameter);

/**
 * @brief Receives data from a connected client.
 *
 * Reads data from a socket connection into the provided buffer, with support for
 * timeout and retry mechanisms.
 *
 * @param sock The socket descriptor for the client connection.
 * @param buffer Pointer to the buffer where the received data will be stored.
 * @param size The maximum number of bytes to read.
 * @param timeout_counter Pointer to a counter tracking timeout occurrences.
 * @param max_timeout The maximum number of allowable timeouts before returning an error.
 * @return The number of bytes received, or a negative value if an error occurs.
 */
int receive_data(int sock, char* buffer, size_t size, uint8_t* timeout_counter, uint8_t max_timeout);

/**
 * @brief Creates and starts the TCP server.
 *
 * Sets up the TCP server to listen for incoming client connections and handle them
 * using the specified parameters.
 *
 * @param pvParameter Pointer to additional parameters for server setup (optional).
 */
void Create_Server(void* pvParameter);

/**
 * @brief Converter for Dbc values to JSON.
 *
 * jSON Converter.
 *
 * @param dbc dbcstruct pointer.
 * @param jsonString json string.
 */
void ConvertToJson(DbcStruct *dbc, char *jsonString);

/**
 * @brief Initializes the TCP server.
 *
 * Configures the necessary components and prepares the ESP32 for running a TCP server.
 */
void Tcp_Init();

#endif /* INCLUDE_TCPSERVER_H_ */
