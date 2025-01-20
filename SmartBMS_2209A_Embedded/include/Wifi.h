/**
 * @file Wifi.h
 * @brief Wi-Fi configuration for ESP32 in AP+STA mode.
 *
 * This header file provides the necessary definitions and function
 * declarations for configuring the ESP32 to operate in both Access Point
 * (AP) and Station (STA) modes.
 *
 * Created on: 18 Dec 2024
 * @author hakimmc
 */

#ifndef WIFI_AP_STA_H
#define WIFI_AP_STA_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "string.h"
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <esp_system.h>
#include <lwip/netdb.h>
#include <ping/ping_sock.h>

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
 * @brief Define this macro to enable Wi-Fi station connection.
 * Comment it out to disable the Wi-Fi station functionality.
 */
#define WIFI_CONNECT

/** 
 * @def AP_SSID
 * @brief SSID for the Access Point.
 */
#define AP_SSID         "Ottomotive_BMS"

/** 
 * @def AP_PASS
 * @brief Password for the Access Point.
 */
#define AP_PASS         "Ottomotive22*"

/** 
 * @def MAX_STA_CONN
 * @brief Maximum number of stations that can connect to the Access Point.
 */
#define MAX_STA_CONN   5

/** 
 * @def MAX_RETRY
 * @brief Maximum number of retry attempts for Wi-Fi connection.
 */
#define MAX_RETRY      5

#ifdef WIFI_CONNECT
    /** 
     * @def WIFI_SSID
     * @brief SSID for the Wi-Fi station connection.
     */
    #define WIFI_SSID   "Poyrazwifi_Calgin"

    /** 
     * @def WIFI_PASS
     * @brief Password for the Wi-Fi station connection.
     */
    #define WIFI_PASS   "Ah487602"

    /** 
     * @def WIFI_TIMEOUT_MS
     * @brief Timeout for Wi-Fi connection in milliseconds.
     */
    #define WIFI_TIMEOUT_MS 10000

    /** 
     * @def ESP32_AP_CHANNEL
     * @brief Channel for the Access Point.
     */
    #define ESP32_AP_CHANNEL        3             

    /** 
     * @def ESP32_MAX_CONN
     * @brief Maximum number of simultaneous connections to the Access Point.
     */
    #define ESP32_MAX_CONN          3
#endif

/**
 * @brief Handles Wi-Fi events.
 *
 * This function is called to process various Wi-Fi events, such as connection
 * establishment and disconnection.
 *
 * @param arg User-provided argument (optional).
 * @param event_base Event base that identifies the event type.
 * @param event_id Event ID specifying the exact event.
 * @param event_data Additional data associated with the event (optional).
 */
void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

/**
 * @brief Initializes the Wi-Fi in AP+STA mode.
 *
 * This function configures the ESP32 to operate in both Access Point (AP)
 * and Station (STA) modes. The configuration is based on the defined macros.
 */
void wifi_init_ap_sta(void);

#endif // WIFI_AP_STA_H
